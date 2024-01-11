#pragma once

#include "type/type.h"

namespace expr {
	class Expression {
	public:
		Expression() = default;

		virtual ~Expression() = default;

		std::shared_ptr<type::Type> type = nullptr;
	};
}