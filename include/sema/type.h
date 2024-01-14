#pragma once

#include "scope.h"
#include "decl/type.h"

namespace sema {
	class Type {
	public:
		explicit Type(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<type::Type> type;
	};
}