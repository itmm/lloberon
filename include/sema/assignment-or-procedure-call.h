#pragma once

#include "scope.h"

namespace sema {
	class Assignment_Or_Procedure_Call {
	public:
		explicit Assignment_Or_Procedure_Call(Scope& scope) :
			scope { scope } { }

		Scope& scope;
	};
}