#pragma once

#include "scope.h"

namespace lloberon {
    class Pointer_Type {
    public:
        Pointer_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}