#pragma once

#include "scope.h"

namespace sema {
	class Procedure_Body {
	public:
		explicit Procedure_Body(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}