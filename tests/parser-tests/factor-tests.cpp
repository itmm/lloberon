#include "parser-tests.h"
#include "expr/variable.h"
#include "const-tests.h"
#include "type-tests.h"

using Factor_Runner = Parser_No_Void_Runner<
	expr::Expression_Ptr, &Parser::parse_factor
>;

TEST(Factor_Tests, empty) {
	Factor_Runner("", true);
}

TEST(Factor_Tests, literals) {
	Factor_Runner test1 { "3" };
	expect_int_value(test1.value, 3);

	Factor_Runner test2 { "3.241" };
	expect_real_value(test2.value, 3.241);

	Factor_Runner test3 { "\"abc\"" };
	expect_string_value(test3.value, "abc");

	Factor_Runner test4 { "020H" };
	expect_int_value(test4.value, 32);

	Factor_Runner test5 { "40X" };
	expect_string_value(test5.value, "@");

	Factor_Runner test6 { "NIL" };
	EXPECT_EQ(test6.value, expr::Expression::nil);

	Factor_Runner test7 { "TRUE" };
	expect_bool_value(test7.value, true);

	Factor_Runner test8 { "FALSE" };
	expect_bool_value(test8.value, false);
}

TEST(Factor_Tests, set) {
	Factor_Runner test1 { "{3..5}" };
}

TEST(Factor_Tests, grouped) {
	Factor_Runner test1 { "(3 + 4)" };
	expect_int_value(test1.value, 7);
}

TEST(Factor_Tests, ident) {
	auto base { std::make_shared<Scope>() };
	base->register_base_types();
	context::scope = std::make_shared<Scope>(base);
	Type_Runner type_runner { "ARRAY 10 OF PROCEDURE(x: BOOLEAN)" };
	context::scope->insert(
		"a", std::make_shared<expr::Variable>(type_runner.value)
	);
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	Factor_Runner test1 { "a" };
	Factor_Runner test2 { "f(3, TRUE)" };
	Factor_Runner test3 { "a[3](TRUE)" };
	context::clear();
}

TEST(Factor_Tests, not) {
	Factor_Runner test1 { "~FALSE" };
	expect_bool_value(test1.value, true);
}

TEST(Factor_Tests, incomplete) {
	context::scope->insert("a", std::make_shared<decl::Procedure>());
	Factor_Runner test1 { "a(3,TRUE", true };
	Factor_Runner test2 { "a(3,", true };
	Factor_Runner test3 { "a(3", true };
	Factor_Runner test4 { "a(", true };
	context::clear();
}