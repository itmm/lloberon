#pragma once

#include "basic/diagnostic.h"
#include "token.h"

#include <map>

#include "llvm/Support/SourceMgr.h"

class Lexer {
public:
	explicit Lexer(llvm::SourceMgr& source_mgr) {
		str_ = source_mgr.getMemoryBuffer(
			source_mgr.getMainFileID()
		)->getBuffer();
		ptr_ = str_.begin();
		token::kind = token::unknown;
	}

	void next();

private:
	llvm::StringRef str_;
	const char* ptr_;

	static std::map<std::string, token::Kind> keywords_;

	void do_comment();

	void form_token(const char* token_end, token::Kind kind);
};