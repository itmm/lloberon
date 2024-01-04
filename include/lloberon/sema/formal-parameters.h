#pragma once

#include "scope.h"

namespace lloberon {
    class Formal_Parameters {
    public:
        Formal_Parameters(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}