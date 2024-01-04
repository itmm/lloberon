#pragma once

#include "scope.h"

namespace lloberon {
    class Field_List {
    public:
        Field_List(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}