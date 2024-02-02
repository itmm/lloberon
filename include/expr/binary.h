#pragma once

#include <utility>

#include "expression.h"
#include "basic/token-kinds.h"

namespace expr {
	class Binary : public Expression {
	public:
		Binary(
			token::Kind kind, Expression_Ptr first,
			Expression_Ptr second
		):
 			Expression { first->type }, kind { kind },
			first { std::move(first) }, second { std::move(second) }
		{ }

		token::Kind kind;
		Expression_Ptr first;
		Expression_Ptr second;

		static std::shared_ptr<Binary> create(
			token::Kind kind, Expression_Ptr first,
			Expression_Ptr second
		) {
			return std::make_shared<Binary>(kind, std::move(first), std::move(second));
		}
	};
}