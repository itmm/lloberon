#pragma once

#include "scope.h"

namespace sema {
	class Expression_List {
	public:
		explicit Expression_List(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}