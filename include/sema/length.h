#pragma once

#include "context.h"
#include "expr/const.h"

namespace sema {
	class Length {
	public:
		explicit Length(int length = 0): length { length } { }

		int length;
	};
}