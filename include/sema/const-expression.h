#pragma once

#include "context.h"
#include "expr/const.h"

namespace sema {
	class Const_Expression {
	public:
		explicit Const_Expression() = default;

		std::shared_ptr<expr::Const> expression;
	};
}