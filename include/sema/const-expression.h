#pragma once

#include "scope.h"
#include "expr/const.h"

namespace sema {
	class Const_Expression {
	public:
		explicit Const_Expression(Scope& scope) : scope { scope } { }

		Scope& scope;
		std::shared_ptr<expr::Const> expression;
	};
}