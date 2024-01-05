#pragma once

#include "scope.h"
#include "declaration.h"

namespace sema {
    class Qual_Ident {
    public:
        Qual_Ident(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() {
            declaration = nullptr;
            module = nullptr;
        }

        std::shared_ptr<Declaration> declaration { nullptr };
        std::shared_ptr<Module_Declaration> module { nullptr };
    private:
        Scope& scope_;
    };
}