#include "parser-tests.h"
#include "decl/type.h"

using Procedure_Type_Runner = Parser_Value_Runner<
	sema::Type, &Parser::parse_procedure_type
>;

TEST(Procedure_Type_Tests, empty) {
	Scope scope;
	sema::Type type { scope };
	Procedure_Type_Runner test1 { "", type, true };
}

TEST(Procedure_Type_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Type type { scope };
	Procedure_Type_Runner test1 { "PROCEDURE (a: INTEGER): BYTE", type };
	auto procedure_type {
		std::dynamic_pointer_cast<type::Procedure>(type.type)
	};
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
}