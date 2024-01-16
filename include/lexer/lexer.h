#pragma once

#include "basic/diagnostic.h"
#include "token.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/SourceMgr.h"

class Keyword_Filter {
public:
	void add_keywords();

	token::Kind get_keyword(
		llvm::StringRef name, token::Kind default_kind = token::unknown
	) {
		auto result = hashtable_.find(name);
		if (result != hashtable_.end()) {
			return result->second;
		}
		return default_kind;
	}

private:
	llvm::StringMap<token::Kind> hashtable_;

	void add_keyword(llvm::StringRef keyword, token::Kind kind);
};

class Lexer {
public:
	explicit Lexer(llvm::SourceMgr& source_mgr, Base_Diagnostic_Engine& diag) :
		diag_ { diag } {
		current_buffer_ = source_mgr.getMainFileID();
		current_str_ = source_mgr.getMemoryBuffer(current_buffer_)->getBuffer();
		current_ptr_ = current_str_.begin();
		keyword_filter_.add_keywords();
		token::kind = token::unknown;
	}

	void next();

	Base_Diagnostic_Engine& diag() { return diag_; }

private:
	Base_Diagnostic_Engine& diag_;
	unsigned current_buffer_;
	llvm::StringRef current_str_;
	const char* current_ptr_;
	Keyword_Filter keyword_filter_;

	void do_comment();

	void form_token(const char* token_end, token::Kind kind);
};