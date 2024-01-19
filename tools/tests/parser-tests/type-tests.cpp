#include "type/type.h"

#include "type-tests.h"

TEST(Type_Tests, empty) {
	context::clear();
	type::Type_Ptr type;
	Type_Runner test1 { "", type, true };
}

TEST(Type_Tests, simple) {
	context::clear();
	context::scope->register_base_types();
	context::scope->insert("Entry", std::make_shared<type::Record>());
	type::Type_Ptr type;
	Type_Runner test1 { "BOOLEAN", type };
	EXPECT_EQ(type, type::Type::base_boolean);

	Type_Runner test2 { "CHAR", type };
	EXPECT_EQ(type, type::Type::base_char);

	Type_Runner test3 { "INTEGER", type };
	EXPECT_EQ(type, type::Type::base_integer);

	Type_Runner test4 { "REAL", type };
	EXPECT_EQ(type, type::Type::base_real);

	Type_Runner test5 { "BYTE", type };
	EXPECT_EQ(type, type::Type::base_byte);

	Type_Runner test6 { "SET", type };
	EXPECT_EQ(type, type::Type::base_set);

	Type_Runner test7 { "ARRAY 10 OF INTEGER", type };
	Type_Runner test8 { "RECORD x, y: INTEGER END", type };
	Type_Runner test9 { "POINTER TO Entry", type };
	Type_Runner test10 { "PROCEDURE (a: INTEGER): INTEGER", type };
}

TEST(Type_Tests, cascading) {
	context::clear();
	context::scope->register_base_types();
	type::Type_Ptr type;
	Type_Runner test1 { "RECORD a: RECORD END END", type };
}

TEST(Type_Tests, invalid) {
	context::clear();
	type::Type_Ptr type;
	Type_Runner test1 { ":", type, true, true };
}