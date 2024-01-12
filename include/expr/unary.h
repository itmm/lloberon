#pragma once

#include "expression.h"
#include "basic/token-kinds.h"

namespace expr {
	class Unary : public Expression {
	public:
		Unary(token::Kind kind, std::shared_ptr<Expression> first):
 			Expression { first->type }, kind { kind }, first { first } { }

		token::Kind kind;
		std::shared_ptr<Expression> first;

		static std::shared_ptr<Unary> create(
			token::Kind kind, std::shared_ptr<Expression> first
		) {
			return std::make_shared<Unary>(kind, first);
		}
	};
}