#pragma once

#include "scope.h"

namespace lloberon::sema {
    class Formal_Parameter_Section {
    public:
        Formal_Parameter_Section(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}