#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "lloberon/lexer/lexer.h"

using namespace lloberon;

namespace char_info {
    LLVM_READNONE inline bool is_whitespace(char c) {
        return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' || c == '\n';
    }

    LLVM_READNONE inline bool is_digit(char c) {
        return c >= '0' && c <= '9';
    }

    LLVM_READNONE inline bool is_letter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
}

void Keyword_Filter::add_keyword(llvm::StringRef keyword, token::Kind kind) {
    hashtable_.insert(std::make_pair(keyword, kind));
}

void Keyword_Filter::add_keywords() {
    #define KEYWORD(name, flags) add_keyword(llvm::StringRef(#name), token::keyword_##name);
    #include "lloberon/basic/token-kinds.def"
}

void Lexer::do_comment() {
    int level { 0 };
    while (*current_ptr_) {
        if (*current_ptr_ == '*' && current_ptr_[1] == ')') {
            --level;
            if (level <= 0) { current_ptr_ += 2; break; }
        } else if (*current_ptr_ == '(' && current_ptr_[1] == '*') {
            ++level;
        }
        ++current_ptr_;
    }
}

void Lexer::next(Token &token) {
    while (*current_ptr_ && char_info::is_whitespace(*current_ptr_)) {
        ++current_ptr_;
    }

    if (!*current_ptr_) { token.kind_ = token::eof; return; }

    if (char_info::is_letter(*current_ptr_)) {
        const char* end = current_ptr_ + 1;
        while (char_info::is_letter(*end) || char_info::is_digit(*end)) { ++end; }
        llvm::StringRef name(current_ptr_, end - current_ptr_);
        token::Kind kind = keyword_filter_.get_keyword(name, token::identifier);
        form_token(token, end, kind);
        return;
    }

    if (char_info::is_digit(*current_ptr_)) {
        const char* end = current_ptr_ + 1;
        bool is_hex { false };
        for (;;) {
            if (char_info::is_digit(*end)) {
                ++end;
            } else if (*end >= 'A' && *end <= 'F') {
                ++end; is_hex = true;
            } else { break; }
        }
        if (*end == 'H') { is_hex = true; ++end; }
        else if (*end == 'X') {
            ++end;
            form_token(token, end, token::string_literal);
            return;
        }
        if (*end == '.') {
            ++end;
            if (is_hex) {
                form_token(token, end, token::unknown);
                return;
            }
            while (char_info::is_digit(*end)) { ++end; }
            if (*end == 'E') {
                ++end;
                if (*end == '+' || *end == '-') { ++end; }
                if (!char_info::is_digit(*end)) {
                    form_token(token, end + 1, token::unknown);
                    return;
                }
                while (char_info::is_digit(*end)) { ++end; }
            }
            form_token(token, end, token::float_literal);
            return;
        }
        form_token(token, end, token::integer_literal);
        return;
    }

    switch (*current_ptr_) {
        #define TOK(ch, kind) case ch: form_token(token, current_ptr_ + 1, kind); break;
        TOK('+', token::plus)
        TOK('-', token::minus)
        TOK('*', token::star)
        TOK('/', token::slash)
        TOK(')', token::right_parenthesis)
        TOK(',', token::comma)
        TOK(';', token::semicolon)
        TOK('=', token::equals)
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
            if (current_ptr_[1] == '.') {
                form_token(token, current_ptr_ + 2, token::range);
            } else {
                form_token(token, current_ptr_ + 1, token::period);
            }
            break;
        case ':':
            if (current_ptr_[1] == '=') {
                form_token(token, current_ptr_ + 2, token::assign);
            } else {
                form_token(token, current_ptr_ + 1, token::colon);
            }
            break;
        case '<':
            if (current_ptr_[1] == '=') {
                form_token(token, current_ptr_ + 2, token::less_or_equal);
            } else {
                form_token(token, current_ptr_ + 1, token::less);
            }
            break;
        case '>':
            if (current_ptr_[1] == '=') {
                form_token(token, current_ptr_ + 2, token::greater_or_equal);
            } else {
                form_token(token, current_ptr_ + 1, token::greater);
            }
            break;
        case '"': {
            const char* end = current_ptr_ + 1;
            while (*end && *end != '"') { ++end; }
            if (!*end) {
                form_token(token, end, token::unknown);
            } else {
                //llvm::outs() << "STRING `" << llvm::StringRef(current_ptr_, end + 1 - current_ptr_) << "'\n";
                form_token(token, end + 1, token::string_literal);
            }
            break;
        }
        case '(':
            if (current_ptr_[1] == '*') {
                do_comment();
                next(token);
            } else {
                form_token(token, current_ptr_ + 1, token::left_parenthesis);
            }
            break;
        default:
            form_token(token, current_ptr_ + 1, token::unknown);
    }
}

void Lexer::form_token(Token &result, const char *token_end, token::Kind kind) {
    result.kind_ = kind;
    result.ptr_ = current_ptr_;
    result.length_ = token_end - current_ptr_;
    current_ptr_ = token_end;
}

#pragma clang diagnostic pop