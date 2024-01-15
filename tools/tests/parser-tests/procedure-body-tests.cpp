#include "parser-tests.h"
#include "decl/variable.h"
#include "decl/type.h"

using Procedure_Body_Runner = Parser_Value_Runner<
	sema::Procedure_Declaration, &Parser::parse_procedure_body
>;

TEST(Procedure_Body_Tests, empty) {
	Context context;
	sema::Procedure_Declaration procedure_declaration { context };
	Procedure_Body_Runner test1 { "", procedure_declaration, true };
}

TEST(Procedure_Body_Tests, simple) {
	Context context;
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Procedure_Declaration procedure_declaration { context };
	Procedure_Body_Runner test1 { "END", procedure_declaration };
	Procedure_Body_Runner test2 { "RETURN 42 END", procedure_declaration };
	Procedure_Body_Runner test3 {
		"BEGIN RETURN 42 END", procedure_declaration
	};
	Procedure_Body_Runner test4 {
		"BEGIN a := 42; RETURN a END", procedure_declaration
	};
}

TEST(Procedure_Body_Tests, with_declaration) {
	auto base { std::make_shared<Scope>() };
	Context context;
	context.scope = std::make_shared<Scope>(base);
	decl::Type::register_base_types(*base);
	sema::Procedure_Declaration procedure_declaration { context };
	Procedure_Body_Runner test1 {
		"VAR a: INTEGER; BEGIN a := 42 END", procedure_declaration
	};

	context.scope->clear();
	Procedure_Body_Runner test2 {
		"CONST a = 42; RETURN a END", procedure_declaration
	};
}

TEST(Procedure_Body_Tests, invalid) {
	Context context;
	sema::Procedure_Declaration procedure_declaration { context };
	Procedure_Body_Runner test1 {
		"RETURN END", procedure_declaration, true, true
	};
}