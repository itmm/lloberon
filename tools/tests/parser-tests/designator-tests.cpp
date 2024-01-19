#include "decl/variable.h"
#include "parser-tests.h"
#include "type/pointer.h"
#include "type-tests.h"

using Designator_Runner = Parser_Value_Runner<
	expr::Expression_Ptr, &Parser::parse_designator
>;

TEST(Designator_Tests, empty) {
	context::clear();
	expr::Expression_Ptr designator;
	Designator_Runner test1 { "", designator, true };
}

TEST(Designator_Tests, simple) {
	auto base { std::make_shared<Scope>() };
	base->register_base_types();
	context::clear();
	context::scope = std::make_shared<Scope>(base);
	expr::Expression_Ptr designator;
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

	context::scope->insert("a", std::make_shared<decl::Variable>(type));
	Designator_Runner test1 { "a", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator->type), nullptr
	);

	Designator_Runner test2 { "a.b", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator->type), nullptr
	);

	Designator_Runner test3 { "a.b.c", designator };
	EXPECT_EQ(designator->type, type::Type::base_integer);

	Designator_Runner test4 { "a.d[2, 3]", designator };
	EXPECT_EQ(designator->type, type::Type::base_byte);

	Designator_Runner test5 { "a.e^", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator->type), nullptr
	);
}

TEST(Designator_Tests, combined) {
	context::clear();
	expr::Expression_Ptr designator;
	type::Type_Ptr type;
	Type_Runner create_type(
		"RECORD "
			"b: ARRAY 10 OF RECORD "
				"c: POINTER TO RECORD END "
			"END "
		"END",
		type
	);
	context::scope->insert("a", std::make_shared<decl::Variable>(type));
	Designator_Runner test1 { "a.b[3].c^", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator->type),
		nullptr
	);
}

TEST(Designator_Tests, incomplete) {
	context::clear();
	expr::Expression_Ptr designator;
	type::Type_Ptr type;
	Type_Runner create_array("ARRAY 10 OF RECORD END", type);
	context::scope->insert("a", std::make_shared<decl::Variable>(type));

	Designator_Runner test1 { "a[3,", designator, true };
	Designator_Runner test2 { "a[3", designator, true };
	Designator_Runner test3 { "a[3,]", designator, true, true };
	Designator_Runner test4 { "a[]", designator, true, true };

	Type_Runner create_record("RECORD b: RECORD END END", type);
	context::scope->insert("b", std::make_shared<decl::Variable>(type));
	Designator_Runner test5 { "b.b.", designator, true };
	Designator_Runner test6 { "b.b.[", designator, true, true };
	Designator_Runner test7 { "b.b.^", designator, true, true };
	Designator_Runner test8 { "b.", designator, true };
	Designator_Runner test9 { "b.[", designator, true, true };
	Designator_Runner test10 { "b.^", designator, true, true };
}