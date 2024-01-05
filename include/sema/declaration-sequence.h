#pragma once

#include "scope.h"

namespace sema {
    class Declaration_Sequence {
    public:
        Declaration_Sequence(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}