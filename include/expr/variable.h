#pragma once

#include "expression.h"

namespace expr {
	class Variable;

	using Variable_Ptr = std::shared_ptr<Variable>;

	class Variable : public Expression {
	public:
		explicit Variable(const std::shared_ptr<type::Type>& type):
			Expression { type } { }

		static Variable_Ptr as_variable(const decl::Declaration_Ptr& declaration) {
			return std::dynamic_pointer_cast<Variable>(declaration);
		}
	};
}