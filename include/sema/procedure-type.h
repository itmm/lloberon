#pragma once

#include "context.h"
#include "type/procedure.h"

namespace sema {
	class Procedure_Type {
	public:
		explicit Procedure_Type(Context& context) : context { context } { }

		Context& context;

		std::shared_ptr<type::Procedure> procedure {
			std::make_shared<type::Procedure>()
		};
	};
}