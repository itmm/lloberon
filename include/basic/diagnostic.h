#pragma once

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>
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
	[[noreturn]] inline void report(unsigned diagnostic_id, Args&& ... arguments) {
		std::string message =  llvm::formatv(
			diag::diagnostic_text(diagnostic_id),
			std::forward<Args>(arguments)...
		).str();
		throw Error { message };
	}
}