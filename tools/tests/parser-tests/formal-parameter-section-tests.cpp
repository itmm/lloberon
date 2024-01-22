#include "parser-tests.h"
#include "type/array.h"

using Formal_Parameter_Section_Runner =
	Parser_Arg_Void_Runner<
	type::Procedure_Ptr, &Parser::parse_formal_parameter_section
>;

TEST(Formal_Parameter_Section_Tests, empty) {
	type::Procedure_Ptr procedure_type;
	Formal_Parameter_Section_Runner("", procedure_type, true);
}

TEST(Formal_Parameter_Section_Tests, simple) {
	context::scope->register_base_types();
	type::Procedure_Ptr procedure_type;
	procedure_type = std::make_shared<type::Procedure>();
	Formal_Parameter_Section_Runner test1 {
		"a: ARRAY OF INTEGER", procedure_type
	};
	EXPECT_EQ(procedure_type->parameters.size(), 1);
	if (! procedure_type->parameters.empty()) {
		const auto& first { procedure_type->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		auto array { std::dynamic_pointer_cast<type::Array>(first.type) };
		EXPECT_NE(array, nullptr);
		if (array) {
			EXPECT_EQ(array->count, -1);
			EXPECT_EQ(array->base, type::Type::base_integer);
		}
		EXPECT_FALSE(first.reference);
	}
	context::clear();
}

TEST(Formal_Parameter_Section_Tests, multiple) {
	context::scope->register_base_types();
	type::Procedure_Ptr procedure_type;
	procedure_type = std::make_shared<type::Procedure>();
	Formal_Parameter_Section_Runner test1 { "a, b: INTEGER", procedure_type };
	EXPECT_EQ(procedure_type->parameters.size(), 2);
	if (procedure_type->parameters.size() >= 2) {
		const auto& first { procedure_type->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		EXPECT_EQ(first.type, type::Type::base_integer);
		EXPECT_FALSE(first.reference);
		const auto& second { procedure_type->parameters[1] };
		EXPECT_STREQ(second.name.c_str(), "b");
		EXPECT_EQ(second.type, type::Type::base_integer);
		EXPECT_FALSE(second.reference);
	}
	context::clear();
}

TEST(Formal_Parameter_Section_Tests, var_parameter) {
	context::scope->register_base_types();
	type::Procedure_Ptr procedure_type;
	procedure_type = std::make_shared<type::Procedure>();
	Formal_Parameter_Section_Runner test1 { "VAR a: INTEGER", procedure_type };
	EXPECT_EQ(procedure_type->parameters.size(), 1);
	if (! procedure_type->parameters.empty()) {
		const auto& first { procedure_type->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		EXPECT_EQ(first.type, type::Type::base_integer);
		EXPECT_TRUE(first.reference);
	}
	context::clear();
}

TEST(Formal_Parameter_Section_Tests, incomplete) {
	context::scope->register_base_types();
	type::Procedure_Ptr procedure_type;
	procedure_type = std::make_shared<type::Procedure>();
	Formal_Parameter_Section_Runner test1 { "VAR", procedure_type, true };
	Formal_Parameter_Section_Runner test2 { "a,", procedure_type, true };
	Formal_Parameter_Section_Runner test3 {
		"a INTEGER", procedure_type, true, true
	};
	context::clear();
}