#pragma once

#include "statement.h"
#include "expr/expression.h"

namespace stmt {
	class While: public Statement {
	public:
		While() = default;

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

		std::vector<Entry> entries;
	};
}