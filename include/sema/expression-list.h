#pragma once

#include "context.h"

namespace sema {
	class Expression_List {
	public:
		explicit Expression_List() = default;

		std::vector<std::shared_ptr<expr::Expression>> list;
	};
}