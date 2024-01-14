#pragma once

#include "scope.h"
#include "expr/const.h"
#include "expr/expression.h"

namespace sema {
	class Expression {
	public:
		explicit Expression(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<expr::Expression> expression;
	};
}