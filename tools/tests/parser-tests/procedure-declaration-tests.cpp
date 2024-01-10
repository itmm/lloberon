#include "parser-tests.h"
#include "decl/variable.h"
#include "decl/type.h"

using Procedure_Declaration_Runner = Parser_Value_Runner<
	sema::Procedure_Declaration, &Parser::parse_procedure_declaration
>;

TEST(Procedure_Declaration_Tests, empty) {
	Scope scope;
	sema::Procedure_Declaration procedure_declaration { scope };
	Procedure_Declaration_Runner test1 { "", procedure_declaration, true };
}

TEST(Procedure_Declaration_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	scope.insert("x", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Procedure_Declaration procedure_declaration { scope };
	Procedure_Declaration_Runner test1 {
		"PROCEDURE Add1(x: INTEGER): INTEGER; RETURN x + 1 END Add1",
		procedure_declaration
	};
}

TEST(Procedure_Declaration_Tests, incomplete) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Declaration procedure_declaration { scope };
	Procedure_Declaration_Runner test1 {
		"PROCEDURE RETURN", procedure_declaration, true, true
	};

	procedure_declaration.clear();
	Procedure_Declaration_Runner test2 {
		"PROCEDURE Answer(): INTEGER; RETURN", procedure_declaration, true
	};
}