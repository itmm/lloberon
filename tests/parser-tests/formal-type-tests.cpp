#include "parser-tests.h"
#include "type/array.h"
#include "decl/module.h"

using Formal_Type_Runner = Parser_No_Void_Runner<
	type::Type_Ptr, &Parser::parse_formal_type
>;

TEST(Formal_Type_Tests, empty) {
	Formal_Type_Runner test1 { "", true };
}

TEST(Formal_Type_Tests, simple) {
	context::scope->register_base_types();
	Formal_Type_Runner test1 { "INTEGER" };
	EXPECT_EQ(test1.value, type::Type::base_integer);
	context::clear();
}

TEST(Formal_Type_Tests, qualified) {
	auto module { std::make_shared<decl::Module>("X") };
	module->insert("Byte", type::Type::base_byte);
	context::scope->insert("X", module);
	Formal_Type_Runner test1 { "X.Byte" };
	EXPECT_EQ(test1.value, type::Type::base_byte);
	context::clear();
}

TEST(Formal_Type_Tests, array) {
	context::scope->register_base_types();
	Formal_Type_Runner test1 { "ARRAY OF BYTE" };
	auto array { std::dynamic_pointer_cast<type::Array>(test1.value) };
	EXPECT_NE(array, nullptr);
	if (array) {
		EXPECT_EQ(array->count, -1);
		EXPECT_EQ(array->base, type::Type::base_byte);
	}
	context::clear();
}

TEST(Formal_Type_Tests, multiple_arrays) {
	context::scope->register_base_types();
	Formal_Type_Runner test1 { "ARRAY OF ARRAY OF BYTE" };
	auto outer { std::dynamic_pointer_cast<type::Array>(test1.value) };
	EXPECT_NE(outer, nullptr);
	if (outer) {
		EXPECT_EQ(outer->count, -1);
		auto inner { std::dynamic_pointer_cast<type::Array>(outer->base) };
		EXPECT_NE(inner, nullptr);
		if (inner) {
			EXPECT_EQ(outer->count, -1);
			EXPECT_EQ(inner->base, type::Type::base_byte);
		}
	}
	context::clear();
}