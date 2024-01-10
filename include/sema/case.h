#pragma once

#include "scope.h"

namespace sema {
	class Case {
	public:
		explicit Case(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}