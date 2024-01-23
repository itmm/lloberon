#include "parser-tests.h"
#include "type/pointer.h"
#include "type-tests.h"

using Designator_Runner = Parser_No_Void_Runner<
	expr::Expression_Ptr, &Parser::parse_designator
>;

TEST(Designator_Tests, empty) {
	Designator_Runner test1 { "", true };
}

TEST(Designator_Tests, simple) {
	auto base { std::make_shared<Scope>() };
	base->register_base_types();
	context::scope = std::make_shared<Scope>(base);
	type::Type_Ptr type;
	Type_Runner create_type(
		"RECORD "
			"b: RECORD "
				"c: INTEGER "
			"END; "
			"d: ARRAY 10, 5 OF BYTE; "
			"e: POINTER TO RECORD END "
		"END",
		type
	);

	context::scope->insert("a", std::make_shared<expr::Variable>(type));
	Designator_Runner test1 { "a" };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(test1.value->type), nullptr
	);

	Designator_Runner test2 { "a.b" };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(test2.value->type), nullptr
	);

	Designator_Runner test3 { "a.b.c" };
	EXPECT_EQ(test3.value->type, type::Type::base_integer);

	Designator_Runner test4 { "a.d[2, 3]" };
	EXPECT_EQ(test4.value->type, type::Type::base_byte);

	Designator_Runner test5 { "a.e^" };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(test5.value->type), nullptr
	);
	context::clear();
}

TEST(Designator_Tests, combined) {
	type::Type_Ptr type;
	Type_Runner create_type(
		"RECORD "
			"b: ARRAY 10 OF RECORD "
				"c: POINTER TO RECORD END "
			"END "
		"END",
		type
	);
	context::scope->insert("a", std::make_shared<expr::Variable>(type));
	Designator_Runner test1 { "a.b[3].c^" };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(test1.value->type), nullptr
	);
	context::clear();
}

TEST(Designator_Tests, incomplete) {
	type::Type_Ptr type;
	Type_Runner create_array("ARRAY 10 OF RECORD END", type);
	context::scope->insert("a", std::make_shared<expr::Variable>(type));

	Designator_Runner test1 { "a[3,", true };
	Designator_Runner test2 { "a[3", true };
	Designator_Runner test3 { "a[3,]", true, true };
	Designator_Runner test4 { "a[]", true, true };

	Type_Runner create_record("RECORD b: RECORD END END", type);
	context::scope->insert("b", std::make_shared<expr::Variable>(type));
	Designator_Runner test5 { "b.b.", true };
	Designator_Runner test6 { "b.b.[", true, true };
	Designator_Runner test7 { "b.b.^", true, true };
	Designator_Runner test8 { "b.", true };
	Designator_Runner test9 { "b.[", true, true };
	Designator_Runner test10 { "b.^", true, true };
	context::clear();
}