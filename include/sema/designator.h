#pragma once

#include "scope.h"

namespace sema {
	class Designator {
	public:
		explicit Designator(Scope& scope) : scope { scope } { }

		Scope& scope;
		std::shared_ptr<expr::Expression> expression;
	};
}