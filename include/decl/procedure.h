#pragma once

#include "decl/declaration-with-scope.h"
#include "type/procedure.h"

namespace decl {
	class Procedure : public Declaration_With_Scope {
	public:
		Procedure() = default;

		std::shared_ptr<type::Procedure> type;
	};
}