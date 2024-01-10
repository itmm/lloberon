#pragma once

#include "scope.h"

namespace sema {
	class Type_Declaration {
	public:
		explicit Type_Declaration(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}