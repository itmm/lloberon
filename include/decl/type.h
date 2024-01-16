#pragma once

#include <memory>
#include <utility>

#include "decl/declaration.h"
#include "type/type.h"

class Scope;

namespace decl {
	class Type : public Declaration {
	public:
		explicit Type(type::Type_Ptr type) :
			Declaration { }, type { std::move(type) } { }

		const type::Type_Ptr type;

		static void register_base_types(Scope& scope);
	};
}