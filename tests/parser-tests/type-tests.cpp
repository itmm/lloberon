#include "type/type.h"

#include "type-tests.h"

TEST(Type_Tests, empty) {
	Type_Runner test1 { "", true };
}

TEST(Type_Tests, simple) {
	context::scope->register_base_types();
	context::scope->insert("Entry", std::make_shared<type::Record>());
	Type_Runner test1 { "BOOLEAN" };
	EXPECT_EQ(test1.value, type::Type::base_boolean);

	Type_Runner test2 { "CHAR" };
	EXPECT_EQ(test2.value, type::Type::base_char);

	Type_Runner test3 { "INTEGER" };
	EXPECT_EQ(test3.value, type::Type::base_integer);

	Type_Runner test4 { "REAL" };
	EXPECT_EQ(test4.value, type::Type::base_real);

	Type_Runner test5 { "BYTE" };
	EXPECT_EQ(test5.value, type::Type::base_byte);

	Type_Runner test6 { "SET" };
	EXPECT_EQ(test6.value, type::Type::base_set);

	Type_Runner test7 { "ARRAY 10 OF INTEGER" };
	Type_Runner test8 { "RECORD x, y: INTEGER END" };
	Type_Runner test9 { "POINTER TO Entry" };
	Type_Runner test10 { "PROCEDURE (a: INTEGER): INTEGER" };
	context::clear();
}

TEST(Type_Tests, cascading) {
	context::scope->register_base_types();
	Type_Runner test1 { "RECORD a: RECORD END END" };
	context::clear();
}

TEST(Type_Tests, invalid) {
	Type_Runner test1 { ":", true, true };
}