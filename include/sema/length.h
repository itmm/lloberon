#pragma once

#include "context.h"
#include "expr/const.h"

namespace sema {
	class Length {
	public:
		explicit Length(Context& context, int length = 0) :
			context { context }, length { length } { }

		Context& context;

		int length;
	};
}