#pragma once

#include "scope.h"
#include "expr/const.h"

namespace sema {
    class Length {
    public:
        explicit Length(Scope& scope, int length = 0): length { length }, scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { length = 0; }

        int length;

    private:
        Scope& scope_;
    };
}