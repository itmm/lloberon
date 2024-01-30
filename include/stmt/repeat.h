#pragma once

#include "statement.h"
#include "expr/const.h"

namespace stmt {
	class Repeat: public Statement {
	public:
		Repeat() = default;

		expr::Expression_Ptr condition;
		Statement_Sequence statements;
	};

	using Repeat_Ptr = std::shared_ptr<Repeat>;
}