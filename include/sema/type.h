#pragma once

#include "context.h"
#include "decl/type.h"

namespace sema {
	class Type {
	public:
		Type() = default;

		std::shared_ptr<type::Type> type;
	};
}