#pragma once

#include "const.h"

namespace expr {
	class Const_Label {
	public:
		Const_Label() = default;

		std::shared_ptr<Const> value;
	};

	class Const_Label_Range {
	public:
		Const_Label_Range() = default;

		Const_Label begin;
		Const_Label end;
	};
}