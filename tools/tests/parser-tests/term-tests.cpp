#include "parser-tests.h"
#include "const-tests.h"

using Term_Runner = Parser_No_Void_Runner<
	expr::Expression_Ptr, &Parser::parse_term
>;

TEST(Term_Tests, empty) {
	Term_Runner test1 { "", true };
}

TEST(Term_Tests, single) {
	Term_Runner test1 { "3" };
	expect_int_value(test1.value, 3);
}

TEST(Term_Tests, simple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	Term_Runner test1 { "a * b" };
	Term_Runner test2 { "a / b" };
	Term_Runner test3 { "a DIV b" };
	Term_Runner test4 { "a MOD b" };
	Term_Runner test5 { "a & b" };
	context::clear();
}

TEST(Term_Tests, multiple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("c", std::make_shared<expr::Variable>(nullptr));
	Term_Runner test1 { "a * b * c" };
	Term_Runner test2 { "a DIV 2 / b" };
	context::clear();
}

TEST(Term_Tests, set) {
	Term_Runner test1 { "{0..3} * {2..5}" };
	expect_set_value(test1.value, 0x000cu);

	Term_Runner test2 { "{0..3} / {2..5}" };
	expect_set_value(test2.value, 0x0033u);
}

TEST(Term_Tests, incomplete) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	Term_Runner test1 { "a / 2 DIV", true };
	Term_Runner test2 { "a /", true };
	context::clear();
}

TEST(Term_Tests, constant_int) {
	Term_Runner test1 { "3 * 5" };
	expect_int_value(test1.value, 15);

	Term_Runner  test2 { "15 / 6" };
	expect_real_value(test2.value, 2.5);

	Term_Runner test3 { "15 DIV 6" };
	expect_int_value(test3.value, 2);

	Term_Runner test4 { "15 MOD 6" };
	expect_int_value(test4.value, 3);
}

TEST(Term_Tests, constant_real) {
	Term_Runner test1 { "3 * 5.0" };
	expect_real_value(test1.value, 15.0);

	Term_Runner  test2 { "15.0 / 6" };
	expect_real_value(test2.value, 2.5);
}

TEST(Term_Tests, constant_bool) {
	Term_Runner test1 { "FALSE & FALSE" };
	expect_bool_value(test1.value, false);

	Term_Runner  test2 { "FALSE & TRUE" };
	expect_bool_value(test2.value, false);

	Term_Runner  test3 { "TRUE & FALSE" };
	expect_bool_value(test3.value, false);

	Term_Runner  test4 { "TRUE & TRUE" };
	expect_bool_value(test4.value, true);
}