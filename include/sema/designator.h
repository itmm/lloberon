#pragma once

#include "context.h"

namespace sema {
	class Designator {
	public:
		explicit Designator() = default;

		std::shared_ptr<expr::Expression> expression;
	};
}