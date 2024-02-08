#pragma once

#include "decl/declaration-with-scope.h"
#include "type/procedure.h"

namespace decl {
	class Procedure;

	using Procedure_Ptr = std::shared_ptr<Procedure>;

	class Procedure : public type::Procedure, public Scope_Mixin {
	public:
		Procedure() = default;

	};
}