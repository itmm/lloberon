#pragma once

#include "scope.h"

namespace sema {
	class Const_Label {
	public:
		explicit Const_Label(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() { value = nullptr; }

		std::shared_ptr<expr::Const> value;

	private:
		Scope& scope_;
	};

	class Const_Label_Range {
	public:
		explicit Const_Label_Range(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		std::shared_ptr<expr::Const> begin;
		std::shared_ptr<expr::Const> end;

	private:
		Scope& scope_;
	};
}