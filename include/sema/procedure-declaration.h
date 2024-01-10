#pragma once

#include "scope.h"

namespace sema {
	class Procedure_Declaration {
	public:
		explicit Procedure_Declaration(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}