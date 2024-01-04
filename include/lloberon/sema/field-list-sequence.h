#pragma once

#include "scope.h"

namespace lloberon {
    class Field_List_Sequence {
    public:
        Field_List_Sequence(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}