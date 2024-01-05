#pragma once

#include "scope.h"

namespace lloberon::sema {
    class Case {
    public:
        Case(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}