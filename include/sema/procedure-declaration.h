#pragma once

#include "decl/procedure.h"
#include "sema/context.h"
#include "sema/ident-def.h"
#include "type/procedure.h"

namespace sema {
	class Procedure_Declaration {
	public:
		Procedure_Declaration() = default;

		Ident_Def name;

		type::Procedure_Ptr procedure_type;

		std::shared_ptr<decl::Procedure> procedure {
			std::make_shared<decl::Procedure>()
		};
	};
}