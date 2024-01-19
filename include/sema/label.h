#pragma once

#include "scope.h"

namespace sema {
	class Const_Label_Range {
	public:
		explicit Const_Label_Range() = default;

		expr::Const_Ptr begin;
		expr::Const_Ptr end;
	};
}