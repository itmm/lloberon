#pragma once

#include "basic/diagnostic.h"
#include "token.h"

#include <map>

#include "llvm/Support/SourceMgr.h"

class Lexer {
public:
	explicit Lexer(llvm::SourceMgr& source_mgr, Base_Diagnostic_Engine& diag) :
		diag_ { diag } {
		current_buffer_ = source_mgr.getMainFileID();
		current_str_ = source_mgr.getMemoryBuffer(current_buffer_)->getBuffer();
		current_ptr_ = current_str_.begin();
		add_keywords();
		token::kind = token::unknown;
	}

	void next();

	Base_Diagnostic_Engine& diag() { return diag_; }

private:
	Base_Diagnostic_Engine& diag_;
	unsigned current_buffer_;
	llvm::StringRef current_str_;
	const char* current_ptr_;

	std::map<std::string, token::Kind> keywords_;

	void add_keywords();

	void do_comment();

	void form_token(const char* token_end, token::Kind kind);
};