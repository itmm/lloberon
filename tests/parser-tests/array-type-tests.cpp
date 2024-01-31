#include "parser-tests.h"
#include "type/array.h"

using Array_Type_Runner = Parser_No_Void_Runner<
	type::Array_Ptr, &Parser::parse_array_type
>;

TEST(Array_Type_Tests, empty) {
	Array_Type_Runner test1 { "", true };
}

TEST(Array_Type_Tests, simple) {
	context::scope->register_base_types();
	Array_Type_Runner test1 { "ARRAY 3 OF BOOLEAN" };
	const auto& array { test1.value };
	EXPECT_NE(array, nullptr);
	EXPECT_NE(array->base, nullptr);
	EXPECT_TRUE(array->base->is_bool());
	EXPECT_EQ(array->count, 3);
	context::clear();
}

TEST(Array_Type_Tests, multiple) {
	context::scope->register_base_types();
	Array_Type_Runner test1 { "ARRAY 3, 4 OF BOOLEAN" };
	const auto& outer { test1.value };
	EXPECT_NE(outer, nullptr);
	EXPECT_EQ(outer->count, 3);
	auto inner { std::dynamic_pointer_cast<type::Array>(outer->base) };
	EXPECT_NE(inner, nullptr);
	EXPECT_EQ(inner->count, 4);
	EXPECT_TRUE(inner->base->is_bool());
	context::clear();
}

TEST(Array_Type_Tests, cascading) {
	context::scope->register_base_types();
	Array_Type_Runner test1 { "ARRAY 3 OF ARRAY 4 OF BOOLEAN" };
	const auto& outer { test1.value };
	EXPECT_NE(outer, nullptr);
	EXPECT_EQ(outer->count, 3);
	auto inner { std::dynamic_pointer_cast<type::Array>(outer->base) };
	EXPECT_NE(inner, nullptr);
	EXPECT_EQ(inner->count, 4);
	EXPECT_TRUE(inner->base->is_bool());
	context::clear();
}