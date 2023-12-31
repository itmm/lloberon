#pragma once

#include "scope.h"

namespace sema {
    class Simple_Expression {
    public:
        Simple_Expression(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}