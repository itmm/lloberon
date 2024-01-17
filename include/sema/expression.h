#pragma once

#include "context.h"
#include "expr/const.h"
#include "expr/expression.h"

namespace sema {
	class Expression {
	public:
		explicit Expression() = default;

		std::shared_ptr<expr::Expression> expression;
	};
}