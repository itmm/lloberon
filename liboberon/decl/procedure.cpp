#include "decl/procedure.h"
#include "sema/scope.h"

decl::Procedure_Ptr decl::Procedure::procedure_odd {
	std::make_shared<decl::Procedure>()
};

void decl::Procedure::register_base_procedures(Scope& scope) {
	scope.insert("ODD", procedure_odd);
}
