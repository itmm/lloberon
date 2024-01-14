#pragma once

#include "scope.h"
#include "stmt/statement.h"

namespace sema {
	class Statement_Sequence {
	public:
		explicit Statement_Sequence(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		stmt::Statement_Sequence sequence;

	private:
		Scope& scope_;
	};
}