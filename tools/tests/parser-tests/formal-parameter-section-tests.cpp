#include "parser-tests.h"
#include "decl/type.h"
#include "type/array.h"

using Formal_Parameter_Section_Runner = Parser_Value_Runner<
	sema::Procedure_Type, &Parser::parse_formal_parameter_section
>;

TEST(Formal_Parameter_Section_Tests, empty) {
	Scope scope;
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameter_Section_Runner("", procedure_type, true);
}

TEST(Formal_Parameter_Section_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameter_Section_Runner test1 {
		"a: ARRAY OF INTEGER", procedure_type
	};
	EXPECT_EQ(procedure_type.procedure->parameters.size(), 1);
	if (! procedure_type.procedure->parameters.empty()) {
		const auto& first { procedure_type.procedure->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		auto array { std::dynamic_pointer_cast<type::Array>(first.type) };
		EXPECT_NE(array, nullptr);
		if (array) {
			EXPECT_EQ(array->count, -1);
			EXPECT_EQ(array->base, type::Type::base_integer);
		}
		EXPECT_FALSE(first.reference);
	}
}

TEST(Formal_Parameter_Section_Tests, multiple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameter_Section_Runner test1 { "a, b: INTEGER", procedure_type };
	EXPECT_EQ(procedure_type.procedure->parameters.size(), 2);
	if (procedure_type.procedure->parameters.size() >= 2) {
		const auto& first { procedure_type.procedure->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		EXPECT_EQ(first.type, type::Type::base_integer);
		EXPECT_FALSE(first.reference);
		const auto& second { procedure_type.procedure->parameters[1] };
		EXPECT_STREQ(second.name.c_str(), "b");
		EXPECT_EQ(second.type, type::Type::base_integer);
		EXPECT_FALSE(second.reference);
	}
}

TEST(Formal_Parameter_Section_Tests, var_parameter) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameter_Section_Runner test1 { "VAR a: INTEGER", procedure_type };
	EXPECT_EQ(procedure_type.procedure->parameters.size(), 1);
	if (! procedure_type.procedure->parameters.empty()) {
		const auto& first { procedure_type.procedure->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		EXPECT_EQ(first.type, type::Type::base_integer);
		EXPECT_TRUE(first.reference);
	}
}

TEST(Formal_Parameter_Section_Tests, incomplete) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameter_Section_Runner test1 { "VAR", procedure_type, true };
	Formal_Parameter_Section_Runner test2 { "a,", procedure_type, true };
	Formal_Parameter_Section_Runner test3 {
		"a INTEGER", procedure_type, true, true
	};
}