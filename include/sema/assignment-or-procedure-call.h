#pragma once

#include "scope.h"

namespace sema {
    class Assignment_Or_Procedure_Call {
    public:
        Assignment_Or_Procedure_Call(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}