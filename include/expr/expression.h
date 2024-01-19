#pragma once

#include <vector>

#include "type/type.h"

namespace expr {
	class Expression: public decl::Declaration {
	public:
		explicit Expression(std::shared_ptr<type::Type> type) :
			type { std::move(type) } { }

		std::shared_ptr<type::Type> type;

		static std::shared_ptr<expr::Expression> nil;
	};

	using Expression_Ptr = std::shared_ptr<Expression>;

	using Expression_List = std::vector<Expression_Ptr>;
}