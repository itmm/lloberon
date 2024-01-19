#include "parser-tests.h"
#include "decl/variable.h"

using Procedure_Declaration_Runner = Parser_String_Runner<
	&Parser::parse_procedure_declaration
>;

TEST(Procedure_Declaration_Tests, empty) {
	Procedure_Declaration_Runner test1 { "", true };
}

TEST(Procedure_Declaration_Tests, simple) {
	context::scope->register_base_types();
	context::scope->insert("x", std::make_shared<decl::Variable>(nullptr));
	Procedure_Declaration_Runner test1 {
		"PROCEDURE Add1(x: INTEGER): INTEGER; RETURN x + 1 END Add1"
	};
	auto declaration { std::dynamic_pointer_cast<decl::Procedure>(
		context::scope->lookup("Add1")
	) };
	EXPECT_NE(declaration, nullptr);
	if (declaration) {
		const auto& type { declaration->type };
		EXPECT_EQ(type->return_type, type::Type::base_integer);
		EXPECT_EQ(type->parameters.size(), 1);
		if (!type->parameters.empty()) {
			const auto& first { type->parameters[0] };
			EXPECT_STREQ(first.name.c_str(), "x");
			EXPECT_FALSE(first.reference);
			EXPECT_EQ(first.type, type::Type::base_integer);
		}
	}
	context::clear();
}

TEST(Procedure_Declaration_Tests, with_declaration) {
	context::scope->register_base_types();
	context::scope->insert("x", std::make_shared<decl::Variable>(nullptr));
	Procedure_Declaration_Runner test1 {
		"PROCEDURE Solution(): INTEGER; CONST a = 42; RETURN a END Solution"
	};
	context::clear();
}

TEST(Procedure_Declaration_Tests, incomplete) {
	auto base { std::make_shared<Scope>() };
	context::scope = std::make_shared<Scope>(base);
	base->register_base_types();
	Procedure_Declaration_Runner test1 { "PROCEDURE RETURN", true, true };
	context::scope->clear();

	Procedure_Declaration_Runner test2 {
		"PROCEDURE Answer(): INTEGER; RETURN", true
	};
	context::clear();
}