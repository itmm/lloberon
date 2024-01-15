#pragma once

#include "context.h"
#include "decl/type.h"

namespace sema {
	class Type {
	public:
		explicit Type(Context& context) : context { context } { }

		Context& context;

		std::shared_ptr<type::Type> type;
	};
}