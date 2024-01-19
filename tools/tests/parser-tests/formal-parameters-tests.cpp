#include "parser-tests.h"
#include "type/type.h"

using Formal_Parameters_Runner = Parser_Value_Runner<
	type::Procedure_Ptr, &Parser::parse_formal_parameters
>;

TEST(Formal_Parameters_Tests, empty) {
	type::Procedure_Ptr procedure_type;
	Formal_Parameters_Runner("", procedure_type, true);
}

TEST(Formal_Parameters_Tests, simple) {
	context::scope->register_base_types();
	type::Procedure_Ptr procedure_type;
	Formal_Parameters_Runner test1 { "()", procedure_type };
	EXPECT_TRUE(procedure_type->parameters.empty());
	EXPECT_EQ(procedure_type->return_type, nullptr);

	Formal_Parameters_Runner test2 { "(VAR a: BYTE)", procedure_type };
	EXPECT_EQ(procedure_type->parameters.size(), 1);
	if (!procedure_type->parameters.empty()) {
		const auto& first { procedure_type->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		EXPECT_EQ(first.type, type::Type::base_byte);
		EXPECT_TRUE(first.reference);
	}
	EXPECT_EQ(procedure_type->return_type, nullptr);
	context::clear();
}

TEST(Formal_Parameters_Tests, with_return) {
	auto module = std::make_shared<decl::Module>("X");
	module->insert("Byte", type::Type::base_byte);
	context::scope->insert("X", module);
	type::Procedure_Ptr procedure_type;
	Formal_Parameters_Runner test1 { "(): X.Byte", procedure_type };
	EXPECT_EQ(procedure_type->parameters.size(), 0);
	const auto& return_type { procedure_type->return_type };
	EXPECT_EQ(return_type, type::Type::base_byte);
	context::clear();
}

TEST(Formal_Parameters_Tests, incomplete) {
	type::Procedure_Ptr procedure_type;
	Formal_Parameters_Runner test1 { "(", procedure_type, true };
	Formal_Parameters_Runner test2 { "():", procedure_type, true };
}