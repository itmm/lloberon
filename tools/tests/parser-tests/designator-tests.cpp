#include "decl/variable.h"
#include "parser-tests.h"
#include "type/pointer.h"
#include "type-tests.h"

using Designator_Runner = Parser_Value_Runner<
	sema::Designator, &Parser::parse_designator
>;

TEST(Designator_Tests, empty) {
	Scope scope;
	sema::Designator designator { scope };
	Designator_Runner test1 { "", designator, true };
}

TEST(Designator_Tests, simple) {
	Scope base;
	decl::Type::register_base_types(base);
	Scope scope { &base };
	sema::Designator designator { scope };
	sema::Type type { scope };
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

	scope.insert("a", std::make_shared<decl::Variable>(type.type));
	Designator_Runner test1 { "a", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator.expression->type),
		nullptr
	);

	Designator_Runner test2 { "a.b", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator.expression->type),
		nullptr
	);

	Designator_Runner test3 { "a.b.c", designator };
	EXPECT_EQ(designator.expression->type, type::Type::base_integer);

	Designator_Runner test4 { "a.d[2, 3]", designator };
	EXPECT_EQ(designator.expression->type, type::Type::base_byte);

	Designator_Runner test5 { "a.e^", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator.expression->type),
		nullptr
	);
}

TEST(Designator_Tests, combined) {
	Scope scope;
	sema::Designator designator { scope };
	sema::Type type { scope };
	Type_Runner create_type(
		"RECORD "
			"b: ARRAY 10 OF RECORD "
				"c: POINTER TO RECORD END "
			"END "
		"END",
		type
	);
	scope.insert("a", std::make_shared<decl::Variable>(type.type));
	Designator_Runner test1 { "a.b[3].c^", designator };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Record>(designator.expression->type),
		nullptr
	);
}

TEST(Designator_Tests, incomplete) {
	Scope scope;
	sema::Designator designator { scope };
	sema::Type type { scope };
	Type_Runner create_array("ARRAY 10 OF RECORD END", type);
	scope.insert("a", std::make_shared<decl::Variable>(type.type));

	Designator_Runner test1 { "a[3,", designator, true };
	Designator_Runner test2 { "a[3", designator, true };
	Designator_Runner test3 { "a[3,]", designator, true, true };
	Designator_Runner test4 { "a[]", designator, true, true };

	Type_Runner create_record("RECORD b: RECORD END END", type);
	scope.insert("b", std::make_shared<decl::Variable>(type.type));
	Designator_Runner test5 { "b.b.", designator, true };
	Designator_Runner test6 { "b.b.[", designator, true, true };
	Designator_Runner test7 { "b.b.^", designator, true, true };
	Designator_Runner test8 { "b.", designator, true };
	Designator_Runner test9 { "b.[", designator, true, true };
	Designator_Runner test10 { "b.^", designator, true, true };
}