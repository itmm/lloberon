#pragma once

#include "type/type.h"

namespace expr {
	class Expression {
	public:
		explicit Expression(std::shared_ptr<type::Type> type) :
			type { std::move(type) } { }

		virtual ~Expression() = default;

		std::shared_ptr<type::Type> type;
	};
}