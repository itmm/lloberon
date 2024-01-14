#pragma once

#include "scope.h"
#include "type/type.h"
#include "stmt/statement.h"
#include "expr/label.h"

namespace sema {
	class Const_Case {
	public:
		explicit Const_Case(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		std::vector<expr::Const_Label_Range> label_ranges;
		stmt::Statement_Sequence sequence;

	private:
		Scope& scope_;
	};

	class Type_Case {
	public:
		explicit Type_Case(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		std::vector<std::shared_ptr<type::Type>> types;
		stmt::Statement_Sequence sequence;

	private:
		Scope& scope_;
	};
}