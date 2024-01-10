#include "parser-tests.h"
#include "decl/type.h"

using Procedure_Type_Runner = Parser_Value_Runner<
	sema::Procedure_Type, &Parser::parse_procedure_type
>;

TEST(Procedure_Type_Tests, empty) {
	Scope scope;
	sema::Procedure_Type procedure_type { scope };
	Procedure_Type_Runner test1 { "", procedure_type, true };
}

TEST(Procedure_Type_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Type procedure_type { scope };
	Procedure_Type_Runner test1 {
		"PROCEDURE (a: INTEGER): INTEGER", procedure_type
	};
}