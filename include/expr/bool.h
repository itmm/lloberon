#pragma once

#include "const.h"

namespace expr {
	class Bool : public Const {
	public:
		explicit Bool(bool value = false) : Const { }, value { value } { }

		bool value;
	};
}