#pragma once

#include "scope.h"
#include "decl/procedure.h"
#include "sema/ident-def.h"
#include "sema/procedure-type.h"

namespace sema {
	class Procedure_Declaration {
	public:
		explicit Procedure_Declaration(Scope& scope) :
			procedure_type { scope }, scope_ { scope } { }

		Scope& scope() { return scope_; }

		Ident_Def name;

		sema::Procedure_Type procedure_type;

		std::shared_ptr<decl::Procedure> procedure {
			std::make_shared<decl::Procedure>()
		};

	private:
		Scope& scope_;
	};
}