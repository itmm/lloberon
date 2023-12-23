#pragma once

#include "lloberon/basic/token-kinds.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include <cstddef>

namespace lloberon {
    class Token {
    public:
        [[nodiscard]] token::Kind kind() const { return kind_; }
        [[nodiscard]] size_t length() const { return length_; }
        [[nodiscard]] llvm::SMLoc location() const { return llvm::SMLoc::getFromPointer(ptr_); }
        [[nodiscard]] llvm::StringRef identifier() const {
            assert(is(token::identifier) && "Cannot get identifier of non-identifier");
            return {ptr_, length_};
        }
        llvm::StringRef literal_data() {
            assert(is_one_of(
                token::integer_literal, token::float_literal,
                token::string_literal
            ) && "Cannot get literal data of non-literal");
            return {ptr_, length_};
        }
        [[nodiscard]] bool is(token::Kind kind) const { return kind == kind_; }
        [[nodiscard]] bool is_one_of(token::Kind kind) const { return is(kind); }
        template<typename ...Args> [[nodiscard]] bool is_one_of(token::Kind first, Args... rest) const {
            return is(first) || is_one_of(rest...);
        }
    private:
        friend class Lexer;
        const char *ptr_;
        size_t length_;
        token::Kind kind_;
    };
}