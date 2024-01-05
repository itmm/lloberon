#pragma once

#include "scope.h"

namespace sema {
    class Case_Statement {
    public:
        Case_Statement(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}