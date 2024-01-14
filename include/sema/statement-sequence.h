#pragma once

#include "scope.h"
#include "stmt/statement.h"

namespace sema {
	class Statement_Sequence {
	public:
		explicit Statement_Sequence(Scope& scope) : scope { scope } { }

		Scope& scope;

		stmt::Statement_Sequence sequence;
	};
}