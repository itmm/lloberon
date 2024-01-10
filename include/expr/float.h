#pragma once

#include "const.h"

namespace expr {
	class Float : public Const {
	public:
		explicit Float(double value = 0.0) : Const { }, value { value } { }

		double value;
	};
}