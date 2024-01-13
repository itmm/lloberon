#pragma once

#include "statement.h"
#include "expr/const.h"
#include "decl/variable.h"

namespace stmt {
	class Repeat: public Statement {
	public:
		Repeat() = default;

		std::shared_ptr<expr::Expression> condition;
		Statement_Sequence statements;
	};
}