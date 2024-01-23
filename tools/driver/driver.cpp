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

	for (auto i { argv_ + 1 }, e { argv_ + argc_ }; i < e; ++i) {
		llvm::outs() << "parsing " << *i << "\n";
		llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> file_or_error =
			llvm::MemoryBuffer::getFile(*i);
		if (std::error_code buffer_error = file_or_error.getError()) {
			llvm::errs() << "Error reading " << *i << ": "
						 << buffer_error.message() << "\n";
			continue;
		}

		llvm::SourceMgr source_mgr;
		source_mgr.AddNewSourceBuffer(std::move(*file_or_error), llvm::SMLoc());
		Lexer lexer { source_mgr };
		Parser parser { lexer };
		try {
			parser.parse();
		} catch (const diag::Error& error) {
			source_mgr.PrintMessage(
				llvm::SMLoc::getFromPointer(token::source),
				llvm::SourceMgr::DK_Error, error.what()
			);
			return 10;
		}
	}
	return 0;
}

