#pragma once

#include "scope.h"

namespace lloberon::sema {
    class For_Statement {
    public:
        For_Statement(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}