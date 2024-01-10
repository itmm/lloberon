#pragma once

#include "scope.h"
#include "decl/type.h"

namespace sema {
	class Type {
	public:
		explicit Type(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { type = nullptr; }

		std::shared_ptr<type::Type> type;
	private:
		Scope& scope_;
	};
}