#pragma once

#include "scope.h"

namespace lloberon {
    class Array_Type {
    public:
        Array_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}