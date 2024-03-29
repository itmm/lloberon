#include "lexer/lexer.h"

namespace char_info {
	LLVM_READNONE inline bool is_whitespace(char c) {
		return c == ' ' || c == '\t' || c == '\f' || c == '\v' ||
			   c == '\r' || c == '\n';
	}

	LLVM_READNONE inline bool is_digit(char c) {
		return c >= '0' && c <= '9';
	}

	LLVM_READNONE inline bool is_letter(char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
}

std::map<std::string, token::Kind> Lexer::keywords_ {
	#define KEYWORD(name, flags) {#name, token::keyword_##name},
	#include "basic/token-kinds.def"
	#undef KEYWORD
};

void Lexer::do_comment() {
	int level { 0 };
	bool done { false };
	while (*ptr_) {
		if (*ptr_ == '*' && ptr_[1] == ')') {
			--level;
			if (level <= 0) {
				done = true;
				ptr_ += 2;
				break;
			}
		} else if (*ptr_ == '(' && ptr_[1] == '*') {
			++level;
		}
		++ptr_;
	}
	if (done) {
		next();
	} else {
		form_token(ptr_, token::unknown);
	}
}

void Lexer::next() {
	while (*ptr_ && char_info::is_whitespace(*ptr_)) {
		++ptr_;
	}

	if (token::kind == token::eof) { return; }

	if (!*ptr_) {
		token::kind = token::eof;
		return;
	}

	if (char_info::is_letter(*ptr_)) {
		const char* end = ptr_ + 1;
		while (char_info::is_letter(*end) || char_info::is_digit(*end)) {
			++end;
		}
		std::string name {ptr_, end };
		auto got { keywords_.find(name) };
		token::Kind kind = got == keywords_.end() ? token::identifier : got->second;
		form_token(end, kind);
		return;
	}

	if (char_info::is_digit(*ptr_)) {
		const char* end = ptr_ + 1;
		bool is_hex { false };
		for (;;) {
			if (char_info::is_digit(*end)) {
				++end;
			} else if (*end >= 'A' && *end <= 'F') {
				++end;
				is_hex = true;
			} else { break; }
		}
		if (*end == 'H') {
			is_hex = true;
			++end;
		} else if (*end == 'X') {
			++end;
			form_token(end, token::char_literal);
			return;
		} else if (is_hex) {
			form_token(end, token::unknown);
			return;
		}
		if (*end == '.' && end[1] != '.') {
			++end;
			if (is_hex) {
				form_token(end, token::unknown);
				return;
			}
			while (char_info::is_digit(*end)) { ++end; }
			if (*end == 'E') {
				++end;
				if (*end == '+' || *end == '-') { ++end; }
				if (!char_info::is_digit(*end)) {
					form_token(end, token::unknown);
					return;
				}
				while (char_info::is_digit(*end)) { ++end; }
			}
			form_token(end, token::float_literal);
			return;
		}
		form_token(end, token::integer_literal);
		return;
	}

	switch (*ptr_) {
		#define TOK(ch, kind) case ch: form_token(ptr_ + 1, kind); break;
		TOK('+', token::plus)
		TOK('-', token::minus)
		TOK('*', token::star)
		TOK('/', token::slash)
		TOK(')', token::right_parenthesis)
		TOK(',', token::comma)
		TOK(';', token::semicolon)
		TOK('=', token::equals)
		TOK('#', token::not_equals)
		TOK('|', token::bar)
		TOK('[', token::left_bracket)
		TOK(']', token::right_bracket)
		TOK('^', token::ptr)
		TOK('&', token::andop)
		TOK('~', token::notop)
		TOK('{', token::left_brace)
		TOK('}', token::right_brace)
		#undef TOK
		case '.':
			if (ptr_[1] == '.') {
				form_token(ptr_ + 2, token::range);
			} else {
				form_token(ptr_ + 1, token::period);
			}
			break;
		case ':':
			if (ptr_[1] == '=') {
				form_token(ptr_ + 2, token::assign);
			} else {
				form_token(ptr_ + 1, token::colon);
			}
			break;
		case '<':
			if (ptr_[1] == '=') {
				form_token(ptr_ + 2, token::less_or_equal);
			} else {
				form_token(ptr_ + 1, token::less);
			}
			break;
		case '>':
			if (ptr_[1] == '=') {
				form_token(ptr_ + 2, token::greater_or_equal);
			} else {
				form_token(ptr_ + 1, token::greater);
			}
			break;
		case '"': {
			const char* end = ptr_ + 1;
			while (*end && *end != '"') { ++end; }
			if (!*end) {
				form_token(end, token::unknown);
			} else {
				form_token(end + 1, token::string_literal);
			}
			break;
		}
		case '(':
			if (ptr_[1] == '*') {
				do_comment();
			} else {
				form_token(ptr_ + 1, token::left_parenthesis);
			}
			break;
		default:
			form_token(ptr_ + 1, token::unknown);
	}
}

void Lexer::form_token(const char* token_end, token::Kind kind) {
	token::kind = kind;
	token::value = std::string {ptr_, token_end };
	token::source = ptr_;
	ptr_ = token_end;
}
