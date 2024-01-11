#pragma once

#include "const.h"

namespace expr {
	class Integer : public Const {
		static std::shared_ptr<type::Type> int_type(int value) {
			if (value >= -128 && value <= 127) {
				return type::Type::base_byte;
			} else {
				return type::Type::base_integer;
			}
		}

	public:
		explicit Integer(int value = 0) :
			Const { int_type(value) }, value { value } { }

		const int value;
	};
}