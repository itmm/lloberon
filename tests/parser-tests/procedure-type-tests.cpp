#include "parser-tests.h"

using Procedure_Type_Runner = Parser_No_Void_Runner<
	type::Procedure_Ptr, &Parser::parse_procedure_type
>;

TEST(Procedure_Type_Tests, empty) {
	Procedure_Type_Runner test1 { "", true };
}

TEST(Procedure_Type_Tests, simple) {
	context::scope->register_base_types();
	Procedure_Type_Runner test1 { "PROCEDURE (a: INTEGER): BYTE" };
	auto procedure_type { test1.value };
	EXPECT_NE(procedure_type, nullptr);
	if (procedure_type) {
		EXPECT_EQ(procedure_type->parameters.size(), 1);
		if (!procedure_type->parameters.empty()) {
			const auto& first { procedure_type->parameters[0] };
			EXPECT_STREQ(first.name.c_str(), "a");
			EXPECT_EQ(first.type, type::Type::base_integer);
			EXPECT_FALSE(first.reference);
		}
		EXPECT_EQ(procedure_type->return_type, type::Type::base_byte);
	}
	context::clear();
}