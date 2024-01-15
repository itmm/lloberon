#pragma once

#include "context.h"

namespace sema {
	class Designator {
	public:
		explicit Designator(Context& context) : context { context } { }

		Context& context;

		std::shared_ptr<expr::Expression> expression;
	};
}