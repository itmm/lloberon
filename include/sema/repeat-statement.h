#pragma once

#include "scope.h"

namespace sema {
	class Repeat_Statement {
	public:
		explicit Repeat_Statement(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}