#pragma once

#include "scope.h"
#include "expr/expression.h"

namespace sema {
	class Expression {
	public:
		explicit Expression(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { expression = nullptr; }

		std::shared_ptr<expr::Expression> expression;

	private:
		Scope& scope_;
	};
}