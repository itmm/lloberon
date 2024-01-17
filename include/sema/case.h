#pragma once

#include "scope.h"
#include "type/type.h"
#include "stmt/statement.h"
#include "expr/label.h"

namespace sema {
	class Const_Case {
	public:
		Const_Case() = default;

		std::vector<expr::Const_Label_Range> label_ranges;
		stmt::Statement_Sequence sequence;
	};

	class Type_Case {
	public:
		Type_Case() = default;

		std::vector<std::shared_ptr<type::Type>> types;
		stmt::Statement_Sequence sequence;
	};
}