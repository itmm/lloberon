#pragma once

#include "const.h"
#include "type/pointer.h"

namespace expr {
	class Nil : public Const {
	public:
		Nil(): Const { type::Pointer::pointer_to_nil } { }
	};
}