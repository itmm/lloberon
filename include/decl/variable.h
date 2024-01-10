#pragma once

#include <utility>

#include "decl/type.h"

namespace decl {
	class Variable : public Declaration {
	public:
		explicit Variable(std::shared_ptr<type::Type> type) :
			Declaration { }, type_ { std::move(type) } { }

		[[nodiscard]] std::shared_ptr<type::Type> type() const { return type_; }

	private:
		std::shared_ptr<type::Type> type_;
	};
}