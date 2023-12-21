#include "lloberon/basic/diagnostic.h"

using namespace lloberon;

namespace {
    const char* diagnostic_texts[] = {
        #define DIAG(id, level, message) message,
        #include "lloberon/basic/diagnostic.def"
    };
    llvm::SourceMgr::DiagKind diagnostic_kinds[] = {
        #define DIAG(id, level, message) llvm::SourceMgr::DK_##level,
        #include "lloberon/basic/diagnostic.def"
    };
}

const char* Diagnostics_Engine::diagnostic_text(unsigned int diagnostic_id) {
    return diagnostic_texts[diagnostic_id];
}

llvm::SourceMgr::DiagKind Diagnostics_Engine::diagnostic_kind(unsigned int diagnostic_id) {
    return diagnostic_kinds[diagnostic_id];
}