#pragma once

#include "scope.h"

namespace sema {
	class Actual_Parameters {
	public:
		explicit Actual_Parameters(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}