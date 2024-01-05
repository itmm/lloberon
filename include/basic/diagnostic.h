#pragma once

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <utility>

namespace lloberon {
    namespace diag {
        enum {
            #define DIAG(id, level, message) id,
            #include "diagnostic.def"
        };
    }

    class Base_Diagnostic_Engine {
    public:
        Base_Diagnostic_Engine() = default;
        virtual ~Base_Diagnostic_Engine() = default;

        template<typename... Args> void report(
                llvm::SMLoc loc, unsigned diagnostic_id, Args&&... arguments
        ) {
            std::string message = llvm::formatv(
                    diagnostic_text(diagnostic_id),
                    std::forward<Args>(arguments)...
            ).str();
            llvm::SourceMgr::DiagKind kind = diagnostic_kind(diagnostic_id);
            report_message(loc, kind, message);
            num_errors_ += (kind == llvm::SourceMgr::DK_Error);
        }

        static const char* diagnostic_text(unsigned diagnostic_id);
        static llvm::SourceMgr::DiagKind diagnostic_kind(unsigned diagnostic_id);

        [[nodiscard]] unsigned num_errors() const { return num_errors_; }

    protected:
        virtual void report_message(
            llvm::SMLoc loc, llvm::SourceMgr::DiagKind kind, const std::string& message
        ) { }

    private:
        unsigned num_errors_ { 0 };
    };

    class Diagnostics_Engine: public Base_Diagnostic_Engine {
    public:
        explicit Diagnostics_Engine(llvm::SourceMgr& source_mgr): source_mgr_ { source_mgr } { }

    protected:
        void report_message(
            llvm::SMLoc loc, llvm::SourceMgr::DiagKind kind, const std::string &message
        ) override {
            source_mgr_.PrintMessage(loc, kind, message);
        }

    private:
        llvm::SourceMgr& source_mgr_;
    };
}