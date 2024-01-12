#pragma once

#include "expression.h"
#include "basic/token-kinds.h"

namespace expr {
	class Binary : public Expression {
	public:
		Binary(
			token::Kind kind, const std::shared_ptr<Expression>& first,
			const std::shared_ptr<Expression>& second
		):
 			Expression { first->type }, kind { kind },
			first { first }, second { second } { }

		token::Kind kind;
		std::shared_ptr<Expression> first;
		std::shared_ptr<Expression> second;

		static std::shared_ptr<Binary> create(
			token::Kind kind, const std::shared_ptr<Expression>& first,
			const std::shared_ptr<Expression>& second
		) {
			return std::make_shared<Binary>(kind, first, second);
		}
	};
}