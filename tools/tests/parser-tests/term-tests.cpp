#include "parser-tests.h"
#include "decl/variable.h"
#include "const-tests.h"

using Term_Runner = Parser_Value_Runner<
	expr::Expression_Ptr, &Parser::parse_term
>;

TEST(Term_Tests, empty) {
	expr::Expression_Ptr term;
	Term_Runner test1 { "", term, true };
}

TEST(Term_Tests, single) {
	expr::Expression_Ptr term;
	Term_Runner test1 { "3", term };
}

TEST(Term_Tests, simple) {
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	expr::Expression_Ptr term;
	Term_Runner test1 { "a * b", term };
	Term_Runner test2 { "a / b", term };
	Term_Runner test3 { "a DIV b", term };
	Term_Runner test4 { "a MOD b", term };
	Term_Runner test5 { "a & b", term };
	context::clear();
}

TEST(Term_Tests, multiple) {
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("c", std::make_shared<decl::Variable>(nullptr));
	expr::Expression_Ptr term;
	Term_Runner test1 { "a * b * c", term };
	Term_Runner test2 { "a DIV 2 / b", term };
	context::clear();
}

TEST(Term_Tests, set) {
	expr::Expression_Ptr term;
	Term_Runner test1 { "{0..3} * {2..5}", term };
	expect_set_value(term, 0x000cu);
	Term_Runner test2 { "{0..3} / {2..5}", term };
	expect_set_value(term, 0x0033u);
}

TEST(Term_Tests, incomplete) {
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	expr::Expression_Ptr term;
	Term_Runner test1 { "a / 2 DIV", term, true };
	Term_Runner test2 { "a /", term, true };
	context::clear();
}

TEST(Term_Tests, constant_int) {
	expr::Expression_Ptr term;
	Term_Runner test1 { "3 * 5", term };
	expect_int_value(term, 15);

	Term_Runner  test2 { "15 / 6", term };
	expect_real_value(term, 2.5);

	Term_Runner test3 { "15 DIV 6", term };
	expect_int_value(term, 2);

	Term_Runner test4 { "15 MOD 6", term };
	expect_int_value(term, 3);
}

TEST(Term_Tests, constant_real) {
	expr::Expression_Ptr term;
	Term_Runner test1 { "3 * 5.0", term };
	expect_real_value(term, 15.0);

	Term_Runner  test2 { "15.0 / 6", term };
	expect_real_value(term, 2.5);
}

TEST(Term_Tests, constant_bool) {
	expr::Expression_Ptr term;
	Term_Runner test1 { "FALSE & FALSE", term };
	expect_bool_value(term, false);

	Term_Runner  test2 { "FALSE & TRUE", term };
	expect_bool_value(term, false);

	Term_Runner  test3 { "TRUE & FALSE", term };
	expect_bool_value(term, false);

	Term_Runner  test4 { "TRUE & TRUE", term };
	expect_bool_value(term, true);
}