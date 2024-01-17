#pragma once

#include "context.h"
#include "expr/expression.h"

namespace sema {
	class Assignment_Or_Procedure_Call {
	public:
		Assignment_Or_Procedure_Call() = default;

		std::shared_ptr<expr::Expression> return_value;
	};
}