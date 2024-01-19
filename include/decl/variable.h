#pragma once

#include <utility>

#include "type/type.h"

namespace decl {
	class Variable : public Declaration {
	public:
		explicit Variable(type::Type_Ptr type) :
			Declaration { }, type_ { std::move(type) } { }

		[[nodiscard]] type::Type_Ptr type() const { return type_; }

	private:
		type::Type_Ptr type_;
	};
}