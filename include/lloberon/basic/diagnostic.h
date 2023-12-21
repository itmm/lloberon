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
            #include "lloberon/basic/diagnostic.def"
        };
    }

    class Diagnostics_Engine {
    public:
        explicit Diagnostics_Engine(llvm::SourceMgr& source_mgr): source_mgr_ { source_mgr } { }

        template<typename... Args> void report(
            llvm::SMLoc loc, unsigned diagnostic_id, Args&&... arguments
        ) {
            std::string message = llvm::formatv(
                diagnostic_text(diagnostic_id),
                std::forward<Args>(arguments)...
            ).str();
            llvm::SourceMgr::DiagKind kind = diagnostic_kind(diagnostic_id);
            source_mgr_.PrintMessage(loc, kind, message);
            num_errors_ += (kind == llvm::SourceMgr::DK_Error);
        }
    private:
        static const char* diagnostic_text(unsigned diagnostic_id);
        static llvm::SourceMgr::DiagKind diagnostic_kind(unsigned diagnostic_id);
        llvm::SourceMgr& source_mgr_;
        unsigned num_errors_ { 0 };
    };
}