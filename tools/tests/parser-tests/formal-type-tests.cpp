#include "parser-tests.h"
#include "type/array.h"

using Formal_Type_Runner = Parser_Value_Runner<
	type::Type_Ptr, &Parser::parse_formal_type
>;

TEST(Formal_Type_Tests, empty) {
	context::clear();
	type::Type_Ptr formal_type;
	Formal_Type_Runner test1 { "", formal_type, true };
}

TEST(Formal_Type_Tests, simple) {
	context::clear();
	context::scope->register_base_types();
	type::Type_Ptr formal_type;
	Formal_Type_Runner test1 { "INTEGER", formal_type };
	EXPECT_EQ(formal_type, type::Type::base_integer);
}

TEST(Formal_Type_Tests, qualified) {
	context::clear();
	auto module { std::make_shared<decl::Module>("X") };
	module->insert("Byte", type::Type::base_byte);
	context::scope->insert("X", module);
	type::Type_Ptr formal_type;
	Formal_Type_Runner test1 { "X.Byte", formal_type };
	EXPECT_EQ(formal_type, type::Type::base_byte);
}

TEST(Formal_Type_Tests, array) {
	context::clear();
	context::scope->register_base_types();
	type::Type_Ptr formal_type;
	Formal_Type_Runner test1 { "ARRAY OF BYTE", formal_type };
	auto array { std::dynamic_pointer_cast<type::Array>(formal_type) };
	EXPECT_NE(array, nullptr);
	if (array) {
		EXPECT_EQ(array->count, -1);
		EXPECT_EQ(array->base, type::Type::base_byte);
	}
}

TEST(Formal_Type_Tests, multiple_arrays) {
	context::clear();
	context::scope->register_base_types();
	type::Type_Ptr formal_type;
	Formal_Type_Runner test1 { "ARRAY OF ARRAY OF BYTE", formal_type };
	auto outer { std::dynamic_pointer_cast<type::Array>(formal_type) };
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
}