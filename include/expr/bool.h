#pragma once

#include "const.h"

namespace expr {
	class Bool : public Const {
	public:
		explicit Bool(bool value = false) :
			Const { type::Type::base_boolean }, value { value } { }

		const bool value;
	};
}