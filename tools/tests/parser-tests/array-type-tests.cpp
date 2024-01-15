#include "parser-tests.h"
#include "decl/type.h"
#include "type/array.h"

using Array_Type_Runner = Parser_Value_Runner<
	sema::Type, &Parser::parse_array_type
>;

TEST(Array_Type_Tests, empty) {
	Context context;
	sema::Type array_type { context };
	Array_Type_Runner test1 { "", array_type, true };
	EXPECT_EQ(array_type.type, nullptr);
}

TEST(Array_Type_Tests, simple) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	sema::Type array_type { context };
	Array_Type_Runner test1 { "ARRAY 3 OF BOOLEAN", array_type };
	auto array { std::dynamic_pointer_cast<type::Array>(array_type.type) };
	EXPECT_NE(array, nullptr);
	EXPECT_NE(array->base, nullptr);
	EXPECT_TRUE(array->base->is_bool());
	EXPECT_EQ(array->count, 3);
}

TEST(Array_Type_Tests, multiple) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	sema::Type array_type { context };
	Array_Type_Runner test1 { "ARRAY 3, 4 OF BOOLEAN", array_type };
	auto outer { std::dynamic_pointer_cast<type::Array>(array_type.type) };
	EXPECT_NE(outer, nullptr);
	EXPECT_EQ(outer->count, 3);
	auto inner { std::dynamic_pointer_cast<type::Array>(outer->base) };
	EXPECT_NE(inner, nullptr);
	EXPECT_EQ(inner->count, 4);
	EXPECT_TRUE(inner->base->is_bool());
}

TEST(Array_Type_Tests, cascading) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	sema::Type array_type { context };
	Array_Type_Runner test1 { "ARRAY 3 OF ARRAY 4 OF BOOLEAN", array_type };
	auto outer { std::dynamic_pointer_cast<type::Array>(array_type.type) };
	EXPECT_NE(outer, nullptr);
	EXPECT_EQ(outer->count, 3);
	auto inner { std::dynamic_pointer_cast<type::Array>(outer->base) };
	EXPECT_NE(inner, nullptr);
	EXPECT_EQ(inner->count, 4);
	EXPECT_TRUE(inner->base->is_bool());
}