#pragma once

#include "scope.h"

namespace sema {
    class Statement_Sequence {
    public:
        Statement_Sequence(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}