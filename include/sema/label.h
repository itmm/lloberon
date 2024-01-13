#pragma once

#include "scope.h"

namespace sema {
	class Const_Label {
	public:
		explicit Const_Label(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

		std::shared_ptr<expr::Const> value;

	private:
		Scope& scope_;
	};

	class Type_Label {
	public:
		explicit Type_Label(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { }

	private:
		Scope& scope_;
	};
}