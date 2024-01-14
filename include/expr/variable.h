#pragma once

#include "expression.h"

namespace expr {
	class Variable : public Expression {
	public:
		explicit Variable(const std::shared_ptr<type::Type>& type):
			Expression { type } { }
	};
}