#pragma once

#include "scope.h"

namespace lloberon::sema {
    class Formal_Type {
    public:
        Formal_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}