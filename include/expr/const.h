#pragma once

#include "expression.h"

namespace expr {
	class Const : public Expression {
	public:
		explicit Const(std::shared_ptr<type::Type> type) :
			Expression { std::move(type) } { }
	};
}