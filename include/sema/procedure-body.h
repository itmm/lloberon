#pragma once

#include "scope.h"

namespace lloberon::sema {
    class Procedure_Body {
    public:
        Procedure_Body(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}