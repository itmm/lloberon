#pragma once

#include "expression.h"

namespace expr {
	class Procedure : public Expression {
	public:
		explicit Procedure(const std::shared_ptr<type::Type>& type):
			Expression { type } { }

		std::shared_ptr<decl::Procedure> procedure;
		std::vector<std::shared_ptr<expr::Expression>> arguments;
	};
}