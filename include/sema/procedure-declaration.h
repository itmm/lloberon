#pragma once

#include "decl/procedure.h"
#include "sema/context.h"
#include "sema/ident-def.h"
#include "sema/procedure-type.h"

namespace sema {
	class Procedure_Declaration {
	public:
		explicit Procedure_Declaration(Context& context) :
			context { context }, procedure_type { context } { }

		Context& context;

		Ident_Def name;

		sema::Procedure_Type procedure_type;

		std::shared_ptr<decl::Procedure> procedure {
			std::make_shared<decl::Procedure>()
		};
	};
}