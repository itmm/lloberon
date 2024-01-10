#pragma once

#include <memory>
#include <utility>

#include "decl/declaration.h"
#include "type/type.h"

class Scope;

namespace decl {
	class Type : public Declaration {
	public:
		explicit Type(std::shared_ptr<type::Type> type) :
			Declaration { }, type { std::move(type) } { }

		std::shared_ptr<type::Type> type;

		static void register_base_types(Scope& scope);
	};
}