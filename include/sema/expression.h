#pragma once

#include "scope.h"
#include "expr/const.h"
#include "expr/expression.h"

namespace sema {
	class Expression {
	public:
		explicit Expression(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { expression = nullptr; }

		std::shared_ptr<expr::Expression> expression;

		[[nodiscard]] std::shared_ptr<expr::Const> as_const() const {
			return expr::Const::as_const(expression);
		}

	private:
		Scope& scope_;
	};
}