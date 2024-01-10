#pragma once

#include "scope.h"

namespace sema {
	class Statement {
	public:
		explicit Statement(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}