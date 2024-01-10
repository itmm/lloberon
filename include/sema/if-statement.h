#pragma once

#include "scope.h"

namespace sema {
	class If_Statement {
	public:
		explicit If_Statement(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}