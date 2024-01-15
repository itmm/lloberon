#pragma once

#include "context.h"

namespace sema {
	class Expression_List {
	public:
		explicit Expression_List(Context& context) : context { context } { }

		Context& context;

		std::vector<std::shared_ptr<expr::Expression>> list;
	};
}