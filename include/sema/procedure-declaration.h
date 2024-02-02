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

		decl::Procedure_Ptr procedure = std::make_shared<decl::Procedure>();
	};
}