#pragma once

#include "context.h"

namespace sema {
	class Actual_Parameters {
	public:
		explicit Actual_Parameters(Context& context) : context { context } { }

		Context& context;
	};
}