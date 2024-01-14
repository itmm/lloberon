#pragma once

#include "scope.h"

namespace sema {
	class Expression_List {
	public:
		explicit Expression_List(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::vector<std::shared_ptr<expr::Expression>> list;
	};
}