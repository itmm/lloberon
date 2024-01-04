#pragma once

#include "scope.h"

namespace lloberon::sema {
    class Var_Declaration {
    public:
        Var_Declaration(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}