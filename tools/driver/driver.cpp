#include "basic/diagnostic.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

#include <llvm/Support/SourceMgr.h>
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/MemoryBuffer.h"

int main(int argc_, const char** argv_) {
	llvm::InitLLVM X(argc_, argv_);

    bool failed { false };
    for (auto i { argv_ + 1 }, e { argv_ + argc_}; i < e; ++i) {
        llvm::outs() << "parsing " << *i << "\n";
        llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> file_or_error =
            llvm::MemoryBuffer::getFile(*i);
        if (std::error_code buffer_error = file_or_error.getError()) {
            llvm::errs() << "Error reading " << *i << ": "
                << buffer_error.message() << "\n";
            continue;
        }

        llvm::SourceMgr source_mgr;
        Diagnostics_Engine diag { source_mgr };
        source_mgr.AddNewSourceBuffer(std::move(*file_or_error), llvm::SMLoc());
        Lexer lexer { source_mgr, diag };
        Parser parser { lexer };
        if (parser.parse()) { failed = true; }
    }
    return failed ? 10 : 0;
}

