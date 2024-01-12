#include "expr/const.h"
#include "parser-tests.h"
#include "const-tests.h"

using Const_Expression_Runner = Parser_Value_Runner<
	sema::Const_Expression, &Parser::parse_const_expression
>;

TEST(Const_Expression_Tests, empty) {
	Scope scope;
	sema::Const_Expression expression { scope };
	Const_Expression_Runner test1 { "", expression, true };
	EXPECT_EQ(expression.expression, nullptr);
}

TEST(Const_Expression_Tests, literals) {
	Scope scope;
	sema::Const_Expression expression { scope };

	Const_Expression_Runner test1 { "234", expression };
	expect_int_value(expression.expression, 234);

	expression.clear();
	Const_Expression_Runner test2 { "-234", expression };
	expect_int_value(expression.expression, -234);

	expression.clear();
	Const_Expression_Runner test3 { "2.34", expression };
	expect_real_value(expression.expression, 2.34);

	expression.clear();
	Const_Expression_Runner test5 { "TRUE", expression };
	expect_bool_value(expression.expression, true);

	expression.clear();
	Const_Expression_Runner test6 { "FALSE", expression };
	expect_bool_value(expression.expression, false);
}

TEST(Const_Expression_Tests, expressions) {
	Scope scope;
	sema::Const_Expression expression { scope };
	Const_Expression_Runner test1 { "3 + 4 * 2", expression };
	expect_int_value(expression.expression, 11);

	expression.clear();
	Const_Expression_Runner test2 { "2 < 4 # FALSE", expression };
	expect_bool_value(expression.expression, true);

	expression.clear();
	Const_Expression_Runner test3 { "5 - 3", expression };
	expect_int_value(expression.expression, 2);

	expression.clear();
	Const_Expression_Runner test4 { "TRUE OR FALSE", expression };
	expect_bool_value(expression.expression, true);
}