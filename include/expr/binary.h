#pragma once

#include <utility>

#include "expression.h"
#include "basic/token-kinds.h"

namespace expr {
	class Binary;

	using Binary_Ptr = std::shared_ptr<Binary>;

	class Binary : public Expression {
	public:
		Binary(
			token::Kind kind, Expression_Ptr first,
			Expression_Ptr second
		):
 			Expression { first->type }, kind { kind },
			first { std::move(first) }, second { std::move(second) }
		{ }

		Binary(
			type::Type_Ptr type, token::Kind kind, Expression_Ptr first,
			Expression_Ptr second
		):
			Expression { std::move(type) }, kind { kind },
			first { std::move(first) }, second { std::move(second) }
		{ }

		token::Kind kind;
		Expression_Ptr first;
		Expression_Ptr second;

		static Binary_Ptr create(
			token::Kind kind, const Expression_Ptr& first,
			const Expression_Ptr& second
		) {
			return std::make_shared<Binary>(kind, first, second);
		}

		static Binary_Ptr create(
			const type::Type_Ptr& type, token::Kind kind,
			const Expression_Ptr& first, const Expression_Ptr& second
		) {
			return std::make_shared<Binary>(type, kind, first, second);
		}
	};
}