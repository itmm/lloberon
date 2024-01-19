#pragma once

#include "statement.h"
#include "expr/const.h"

namespace stmt {
	class For: public Statement {
	public:
		For() = default;

		std::shared_ptr<expr::Variable> variable;
		std::shared_ptr<expr::Expression> begin;
		std::shared_ptr<expr::Expression> end;
		std::shared_ptr<expr::Const> increment;
		Statement_Sequence statements;
	};
}