#pragma once

#include "scope.h"

namespace sema {
	class Expression_List {
	public:
		explicit Expression_List(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		std::vector<std::shared_ptr<expr::Expression>> list;

	private:
		Scope& scope_;
	};
}