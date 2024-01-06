#pragma once

#include "decl/declaration-with-scope.h"

namespace decl {
    class Procedure : public Declaration_With_Scope {
    public:
        Procedure(Declaration *enclosing_declaration, llvm::SMLoc loc, std::string name) :
            Declaration_With_Scope { DK_Proc, enclosing_declaration, loc, std::move(name) }
        { }

        static bool classof(const Declaration *declaration) {
            return declaration && declaration->kind() == DK_Proc;
        }
    };
}