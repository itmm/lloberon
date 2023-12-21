#pragma once

#include "lloberon/basic/token-kinds.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include <cstddef>

namespace lloberon {
    class Token {
    public:
        [[nodiscard]] token::Token_Kind kind() const { return kind_; }
        [[nodiscard]] size_t length() const { return length_; }
        [[nodiscard]] llvm::SMLoc location() const { return llvm::SMLoc::getFromPointer(ptr_); }
        llvm::StringRef identifier() {
            assert(is(token::identifier) && "Cannot get identifier of non-identifier");
            return {ptr_, length_};
        }
        /*
        llvm::StringRef literal_data() {
            assert(is_one_of(token::integer_literal, token::string_literal) && "Cannot get literal data of non-literal");
            return {ptr_, length_};
        }
         */
        bool is(token::Token_Kind kind) { return kind == kind_; }
        bool is_one_of(token::Token_Kind kind) { return is(kind); }
        template<typename ...Args> bool is_one_of(token::Token_Kind first, Args... rest) {
            return is(first) || is_one_of(rest...);
        }
    private:
        friend class Lexer;
        const char *ptr_;
        size_t length_;
        token::Token_Kind kind_;
    };
}