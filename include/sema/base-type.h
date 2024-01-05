#pragma once

#include "scope.h"

namespace sema {
    class Base_Type {
    public:
        Base_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}