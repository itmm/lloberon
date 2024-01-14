#pragma once

#include "expression.h"

namespace expr {
	class Procedure : public Expression {
	public:
		explicit Procedure(const std::shared_ptr<type::Type>& type):
			Expression { type } { }
	};
}