#pragma once

#include "scope.h"
#include "expr/const.h"

namespace sema {
    class Const_Expression {
    public:
        explicit Const_Expression(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { expression = nullptr; }

        std::shared_ptr<expr::Const> expression;

    private:
        Scope& scope_;
    };
}