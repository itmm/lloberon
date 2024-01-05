#pragma once

#include "scope.h"
#include "declaration.h"

namespace lloberon::sema {
    class Qual_Ident {
    public:
        Qual_Ident(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { declaration = module = nullptr; }

        Declaration* declaration { nullptr };
        Module_Declaration* module { nullptr };
    private:
        Scope& scope_;
    };
}