#pragma once

#include "scope.h"
#include "type/procedure.h"

namespace sema {
	class Procedure_Type {
	public:
		explicit Procedure_Type(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<type::Procedure> procedure {
			std::make_shared<type::Procedure>()
		};
	};
}