#pragma once

#include "scope.h"
#include "expr/const.h"

namespace sema {
	class Length {
	public:
		explicit Length(Scope& scope, int length = 0) :
			scope { scope }, length { length } { }

		Scope& scope;

		int length;
	};
}