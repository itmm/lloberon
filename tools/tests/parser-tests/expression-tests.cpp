#include "parser-tests.h"
#include "expr/expression.h"
#include "const-tests.h"

using Expression_Runner = Parser_Value_Runner<
	expr::Expression_Ptr, &Parser::parse_expression
>;

TEST(Expression_Tests, empty) {
	expr::Expression_Ptr expression;
	Expression_Runner test1 { "", expression, true };
}

TEST(Expression_Tests, single) {
	context::scope->register_base_types();
	expr::Expression_Ptr expression;
	Expression_Runner test1 { "3 = 4", expression };
	Expression_Runner test2 { "3 # 4", expression };
	Expression_Runner test3 { "3 < 4", expression };
	Expression_Runner test4 { "3 <= 4", expression };
	Expression_Runner test5 { "3 > 4", expression };
	Expression_Runner test6 { "3 >= 4", expression };
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	Expression_Runner test7 { "3 IN a", expression };
	Expression_Runner test8 { "a IS INTEGER", expression };
	Expression_Runner test9 { "NIL", expression };
	EXPECT_EQ(expression, expr::Expression::nil);
	context::clear();
}

TEST(Expression_Tests, multiple) {
	expr::Expression_Ptr expression;
	Expression_Runner test1 { "3 < 4 = TRUE", expression };
}

TEST(Expression_Tests, set) {
	expr::Expression_Ptr expression;
	Expression_Runner test1 { "{1..2} = {2,1}", expression };
	expect_bool_value(expression, true);

	Expression_Runner test2 { "{1..2} = {2}", expression };
	expect_bool_value(expression, false);

	Expression_Runner test3 { "{1..2} # {2,1}", expression };
	expect_bool_value(expression, false);

	Expression_Runner test4 { "{1..2} # {2}", expression };
	expect_bool_value(expression, true);

	Expression_Runner test5 { "2 IN {0..3}", expression };
	expect_bool_value(expression, true);

	Expression_Runner test6 { "4 IN {0..3}", expression };
	expect_bool_value(expression, false);
}

TEST(Expression_Tests, invalid) {
	expr::Expression_Ptr expression;
	Expression_Runner test1 { "}", expression, true, true };
}