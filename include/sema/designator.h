#pragma once

#include "scope.h"

namespace sema {
	class Designator {
	public:
		explicit Designator(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

	private:
		Scope& scope_;
	};
}