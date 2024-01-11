#pragma once

#include "expression.h"
#include "type/pointer.h"

namespace expr {
	class Nil : public Expression {
	public:
		Nil(): Expression { type::Pointer::pointer_to_nil } { }
	};
}