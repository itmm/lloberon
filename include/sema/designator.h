#pragma once

#include "scope.h"

namespace sema {
    class Designator {
    public:
        Designator(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}