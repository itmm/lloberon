#pragma once

#include "scope.h"

namespace sema {
	class Const_Label {
	public:
		explicit Const_Label(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<expr::Const> value;
	};

	class Const_Label_Range {
	public:
		explicit Const_Label_Range(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<expr::Const> begin;
		std::shared_ptr<expr::Const> end;
	};
}