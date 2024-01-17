#include "decl/variable.h"
#include "const-tests.h"
#include "parser-tests.h"

using Simple_Expression_Runner = Parser_Value_Runner<
	sema::Expression, &Parser::parse_simple_expression
>;

TEST(Simple_Expression_Tests, empty) {
	context::clear();
	sema::Expression simple_expression;
	Simple_Expression_Runner test1 { "", simple_expression, true };
}

void expect_int(const char* source, int expected) {
	context::clear();
	sema::Expression expression;
	Simple_Expression_Runner runner { source, expression };
	expect_int_value(expression.expression, expected);
}

void expect_real(const char* source, double expected) {
	context::clear();
	sema::Expression expression;
	Simple_Expression_Runner runner { source, expression };
	expect_real_value(expression.expression, expected);
}

TEST(Simple_Expression_Tests, single) {
	expect_int("345", 345);
}

TEST(Simple_Expression_Tests, simple) {
	expect_int("-5", -5);
	expect_int("3 + 4", 7);
	expect_int("3 - 4", -1);

	expect_real("-3.5", -3.5);
	expect_real("2.5 + 5.25", 7.75);
	expect_real("2.5 - 5.25", -2.75);

	expect_real("2.5 + 5", 7.5);
	expect_real("3 - 6.5", -3.5);

	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	sema::Expression simple_expression;
	Simple_Expression_Runner test3 { "a OR b", simple_expression };
}

void expect_bool(const char* source, bool expected) {
	context::clear();
	sema::Expression expression;
	Simple_Expression_Runner runner { source, expression };
	expect_bool_value(expression.expression, expected);
}

void expect_true(const char* source) { expect_bool(source, true); }

void expect_false(const char* source) { expect_bool(source, false); }

TEST(Simple_Expression_Tests, constant_or) {
	expect_false("FALSE OR FALSE");
	expect_true("FALSE OR TRUE");
	expect_true("TRUE OR TRUE");
	expect_true("TRUE OR TRUE");
}

TEST(Simple_Expression_Tests, factor) {
	expect_int("3 * 4", 12);
	expect_real("3 / 2 + 4 * 3", 13.5);
}

TEST(Simple_Expression_Tests, unaries) {
	expect_int("+3", 3);
	expect_int("-3 + 4", 1);

	context::clear();
	sema::Expression simple_expression;
	Simple_Expression_Runner test3 { "+-3", simple_expression, true, true };
}

TEST(Simple_Expression_Tests, set) {
	context::clear();
	sema::Expression simple_expression;
	Simple_Expression_Runner test1 { "{0..3} + {2..5}", simple_expression };
	expect_set_value(simple_expression.expression, 0x003fu);

	Simple_Expression_Runner test2 { "{0..3} - {2..5}", simple_expression };
	expect_set_value(simple_expression.expression, 0x0003u);
}

TEST(Simple_Expression_Tests, incomplete) {
	context::clear();
	sema::Expression simple_expression;
	Simple_Expression_Runner test1 { "3 +", simple_expression, true };
	Simple_Expression_Runner test2 { "+", simple_expression, true };
}