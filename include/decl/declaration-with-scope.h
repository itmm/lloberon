#pragma once

#include "llvm/Support/SMLoc.h"

#include "sema/scope.h"
#include "decl/declaration.h"

namespace decl {
    class Declaration_With_Scope : public Declaration {
    public:
        Declaration_With_Scope(
            Declaration::Kind kind, Declaration* enclosing_declaration,
            llvm::SMLoc loc, const std::string &name
        ) :
            Declaration(kind, enclosing_declaration, loc, name)
        {}

        std::shared_ptr<decl::Declaration> lookup(const std::string &name) {
            return scope_.lookup(name);
        }

        bool insert(const std::shared_ptr<decl::Declaration> &declaration) {
            return scope_.insert(declaration);
        }

    private:
        Scope scope_;
    };
}