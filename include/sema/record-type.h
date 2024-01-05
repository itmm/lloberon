#pragma once

#include "scope.h"

namespace sema {
    class Record_Type {
    public:
        Record_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { }

    private:
        Scope& scope_;
    };
}