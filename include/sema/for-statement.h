#pragma once

#include "scope.h"

namespace sema {
	class For_Statement {
	public:
		explicit For_Statement(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}