#pragma once

#include "scope.h"

namespace sema {
    class Case_List {
    public:
        Case_List(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}