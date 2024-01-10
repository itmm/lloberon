#pragma once

#include "scope.h"

namespace sema {
	class Var_Declaration {
	public:
		explicit Var_Declaration(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}