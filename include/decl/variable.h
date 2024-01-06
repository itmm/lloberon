#pragma once

#include "decl/type.h"

namespace decl {
    class Variable : public Declaration {
    public:
        Variable(
                Declaration *enclosing_declaration, llvm::SMLoc loc,
                std::string name, Type *type
        ) :
                Declaration(DK_Var, enclosing_declaration, loc, std::move(name)),
                type_{type} {}

        Type* type() { return type_; }

        static bool classof(const Declaration *declaration) {
            return declaration && declaration->kind() == DK_Var;
        }

    private:
        Type* type_;
    };
}