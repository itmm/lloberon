#pragma once

#include "context.h"
#include "type/procedure.h"

namespace sema {
	class Procedure_Type {
	public:
		Procedure_Type() = default;

		std::shared_ptr<type::Procedure> procedure {
			std::make_shared<type::Procedure>()
		};
	};
}