#pragma once

#include "decl/declaration-with-scope.h"
#include "type/procedure.h"

namespace decl {
	class Procedure;

	using Procedure_Ptr = std::shared_ptr<Procedure>;

	class Procedure : public Declaration_With_Scope {
	public:
		Procedure() = default;

		std::shared_ptr<type::Procedure> type;

		static Procedure_Ptr procedure_odd;

		static void register_base_procedures(Scope& scope);
	};
}