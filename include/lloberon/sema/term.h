#pragma once

#include "scope.h"

namespace lloberon::sema {
    class Term {
    public:
        Term(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}