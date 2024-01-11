#pragma once

#include "const.h"

namespace expr {
	class Real : public Const {
	public:
		explicit Real(double value = 0.0) :
			Const { type::Type::base_real }, value { value } { }

		const double value;
	};
}