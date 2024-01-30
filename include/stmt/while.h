#pragma once

#include <utility>

#include "statement.h"
#include "expr/expression.h"

namespace stmt {
	class While: public Statement {
	public:
		While() = default;

		struct Entry {
			Entry(
				expr::Expression_Ptr  condition, Statement_Sequence&& statements
			):
 				condition { std::move(condition) },
				statements { std::move(statements) }
			{ }

			expr::Expression_Ptr condition;
			Statement_Sequence statements;
		};

		std::vector<Entry> entries;
	};

	using While_Ptr = std::shared_ptr<While>;
}