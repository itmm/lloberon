#pragma once

#include "expression.h"
#include "basic/token-kinds.h"

namespace expr {
	class Unary;

	using Unary_Ptr = std::shared_ptr<Unary>;

	class Unary : public Expression {
	public:
		Unary(token::Kind kind, Expression_Ptr first):
			Expression { first->type }, kind { kind },
			first { std::move(first) }
		{ }

		Unary(type::Type_Ptr type, token::Kind kind, Expression_Ptr first):
 			Expression { std::move(type) }, kind { kind },
			first { std::move(first) }
		{ }

		token::Kind kind;
		Expression_Ptr first;

		static Unary_Ptr create(token::Kind kind, const Expression_Ptr& first) {
			return std::make_shared<Unary>(kind, first);
		}

		static Unary_Ptr create(
			const type::Type_Ptr& type, token::Kind kind, const Expression_Ptr& first
		) {
			return std::make_shared<Unary>(type, kind, first);
		}
	};
}