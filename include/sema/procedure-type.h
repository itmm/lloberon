#pragma once

#include "scope.h"

namespace sema {
    class Procedure_Type {
    public:
        Procedure_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}