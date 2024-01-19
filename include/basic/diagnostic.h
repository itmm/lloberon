#pragma once

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <utility>

namespace diag {
	enum {
		#define DIAG(id, message) id,

		#include "diagnostic.def"
	};

	const char* diagnostic_text(unsigned diagnostic_id);

	class Error: public std::exception {
	public:
		explicit Error(std::string  what): what_ { std::move(what) } { }

		[[nodiscard]] const char* what() const noexcept override {
			return what_.c_str();
		}

	private:
		std::string what_;
	};

	template<typename... Args>
	inline void report(unsigned diagnostic_id, Args&& ... arguments) {
		std::string message = llvm::formatv(
			diag::diagnostic_text(diagnostic_id),
			std::forward<Args>(arguments)...
		).str();
		throw Error { message };
	}
}

class Base_Diagnostic_Engine {
public:
	Base_Diagnostic_Engine() = default;

	virtual ~Base_Diagnostic_Engine() = default;

	template<typename... Args>
	void report(
		llvm::SMLoc loc, unsigned diagnostic_id, Args&& ... arguments
	) {
		std::string message = llvm::formatv(
			diag::diagnostic_text(diagnostic_id),
			std::forward<Args>(arguments)...
		).str();
		report_message(loc, llvm::SourceMgr::DK_Error, message);
		++num_errors_;
	}

	[[nodiscard]] unsigned num_errors() const { return num_errors_; }

protected:
	virtual void report_message(
		llvm::SMLoc loc, llvm::SourceMgr::DiagKind kind,
		const std::string& message
	) { }

private:
	unsigned num_errors_ { 0 };
};

class Diagnostics_Engine : public Base_Diagnostic_Engine {
public:
	explicit Diagnostics_Engine(llvm::SourceMgr& source_mgr) :
		source_mgr_ { source_mgr } { }

protected:
	void report_message(
		llvm::SMLoc loc, llvm::SourceMgr::DiagKind kind,
		const std::string& message
	) override {
		source_mgr_.PrintMessage(loc, kind, message);
	}

private:
	llvm::SourceMgr& source_mgr_;
};