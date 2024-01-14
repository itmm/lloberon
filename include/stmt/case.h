#pragma once

#include "statement.h"
#include "expr/expression.h"

namespace stmt {
	class Const_Case: public Statement {
	public:
		Const_Case() = default;

		struct Entry {
			Entry(
				const std::shared_ptr<expr::Expression>& condition,
				Statement_Sequence&& statements
			):
				condition { condition }, statements { std::move(statements) }
			{ }

			std::shared_ptr<expr::Expression> condition;
			Statement_Sequence statements;
		};

		std::shared_ptr<expr::Expression> condition;
		std::vector<Entry> entries;
	};

	class Type_Case: public Statement {
	public:
		Type_Case() = default;

		struct Entry {
			Entry(
				const std::shared_ptr<expr::Expression>& condition,
				Statement_Sequence&& statements
			):
 				condition { condition }, statements { std::move(statements) }
			{ }

			std::shared_ptr<expr::Expression> condition;
			Statement_Sequence statements;
		};

		std::shared_ptr<expr::Expression> condition;
		std::vector<Entry> entries;
	};
}