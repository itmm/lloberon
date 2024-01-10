#pragma once

#include "scope.h"

namespace sema {
	class Formal_Parameters {
	public:
		explicit Formal_Parameters(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}