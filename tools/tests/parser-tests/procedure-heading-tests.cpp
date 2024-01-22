#include "parser-tests.h"

using Procedure_Heading_Runner = Parser_Arg_Void_Runner<
	sema::Procedure_Declaration, &Parser::parse_procedure_heading
>;

TEST(Procedure_Heading_Tests, empty) {
	sema::Procedure_Declaration procedure_declaration;
	Procedure_Heading_Runner test1 { "", procedure_declaration, true };
}

TEST(Procedure_Heading_Tests, simple) {
	context::scope->register_base_types();
	sema::Procedure_Declaration procedure_declaration;
	Procedure_Heading_Runner test1 {
		"PROCEDURE f(x: INTEGER): INTEGER", procedure_declaration
	};
	const auto& type { procedure_declaration.procedure->type };
	EXPECT_EQ(type->return_type, type::Type::base_integer);
	EXPECT_EQ(type->parameters.size(), 1);
	if (!type->parameters.empty()) {
		const auto& first { type->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "x");
		EXPECT_FALSE(first.reference);
		EXPECT_EQ(first.type, type::Type::base_integer);
	}
	context::clear();
}

TEST(Procedure_Heading_Tests, incomplete) {
	context::scope->register_base_types();
	sema::Procedure_Declaration procedure_declaration;
	Procedure_Heading_Runner test1 {
		"PROCEDURE f", procedure_declaration, true
	};

	Procedure_Heading_Runner test2 {
		"PROCEDURE (): INTEGER", procedure_declaration, true, true
	};
	context::clear();
}