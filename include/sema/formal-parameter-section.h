#pragma once

#include "scope.h"

namespace sema {
	class Formal_Parameter_Section {
	public:
		explicit Formal_Parameter_Section(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}