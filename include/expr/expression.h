#pragma once

#include <vector>

#include "type/type.h"

namespace expr {
	class Expression;

	using Expression_Ptr = std::shared_ptr<Expression>;

	class Expression: public decl::Declaration {
	public:
		explicit Expression(type::Type_Ptr type): type { std::move(type) } { }

		type::Type_Ptr type;

		static expr::Expression_Ptr nil;
	};

	using Expression_List = std::vector<Expression_Ptr>;
}