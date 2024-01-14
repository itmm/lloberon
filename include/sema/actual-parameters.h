#pragma once

#include "scope.h"

namespace sema {
	class Actual_Parameters {
	public:
		explicit Actual_Parameters(Scope& scope) : scope { scope } { }

		Scope& scope;
	};
}