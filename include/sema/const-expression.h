#pragma once

#include "context.h"
#include "expr/const.h"

namespace sema {
	class Const_Expression {
	public:
		explicit Const_Expression(Context& context) : context { context } { }

		Context& context;

		std::shared_ptr<expr::Const> expression;
	};
}