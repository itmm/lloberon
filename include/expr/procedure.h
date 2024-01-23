#pragma once

#include "expression.h"

namespace expr {
	class Procedure;

	using Procedure_Ptr = std::shared_ptr<Procedure>;

	class Procedure : public Expression {
	public:
		explicit Procedure(const type::Type_Ptr& type): Expression { type } { }

		std::shared_ptr<decl::Procedure> procedure;
		std::vector<expr::Expression_Ptr> arguments;

		static Procedure_Ptr as_procedure(
			const decl::Declaration_Ptr& declaration
		) {
			return std::dynamic_pointer_cast<Procedure>(declaration);
		}
	};
}