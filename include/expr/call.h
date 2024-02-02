#pragma once

#include "expression.h"
#include "type/procedure.h"

namespace expr {
	class Call;

	using Call_Ptr = std::shared_ptr<Call>;

	class Call : public Expression {
	public:
		explicit Call(const type::Type_Ptr& type): Expression { type } { }

		decl::Declaration_Ptr procedure;
		expr::Expression_List arguments;

		static Call_Ptr as_call(const decl::Declaration_Ptr& declaration) {
			return std::dynamic_pointer_cast<Call>(declaration);
		}
	};
}