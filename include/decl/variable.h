#pragma once

#include "decl/type.h"

namespace decl {
    class Variable : public Declaration {
    public:
        Variable(
                Declaration *enclosing_declaration, llvm::SMLoc loc,
                std::string name, Type *type
        ) :
                Declaration(enclosing_declaration, loc, std::move(name)),
                type_{type} {}

        Type* type() { return type_; }

    private:
        Type* type_;
    };
}