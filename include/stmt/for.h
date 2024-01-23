#pragma once

#include "statement.h"
#include "expr/const.h"
#include "expr/variable.h"

namespace stmt {
	class For: public Statement {
	public:
		For() = default;

		expr::Variable_Ptr variable;
		expr::Expression_Ptr begin;
		expr::Expression_Ptr end;
		expr::Const_Ptr increment;
		Statement_Sequence statements;
	};

	using For_Ptr = std::shared_ptr<For>;
}