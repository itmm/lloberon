#include "parser-tests.h"
#include "decl/variable.h"
#include "expr/expression.h"
#include "const-tests.h"

using Expression_Runner = Parser_Value_Runner<
	sema::Expression, &Parser::parse_expression
>;

TEST(Expression_Tests, empty) {
	Context context;
	sema::Expression expression { context };
	Expression_Runner test1 { "", expression, true };
}

TEST(Expression_Tests, single) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context.scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	sema::Expression expression { context };
	Expression_Runner test1 { "3 = 4", expression };
	Expression_Runner test2 { "3 # 4", expression };
	Expression_Runner test3 { "3 < 4", expression };
	Expression_Runner test4 { "3 <= 4", expression };
	Expression_Runner test5 { "3 > 4", expression };
	Expression_Runner test6 { "3 >= 4", expression };
	Expression_Runner test7 { "3 IN a", expression };
	Expression_Runner test8 { "a IS INTEGER", expression };
	Expression_Runner test9 { "NIL", expression };
	EXPECT_EQ(expression.expression, expr::Expression::nil);
}

TEST(Expression_Tests, multiple) {
	Context context;
	sema::Expression expression { context };
	Expression_Runner test1 { "3 < 4 = TRUE", expression };
}

TEST(Expression_Tests, set) {
	Context context;
	sema::Expression expression { context };
	Expression_Runner test1 { "{1..2} = {2,1}", expression };
	expect_bool_value(expression.expression, true);

	Expression_Runner test2 { "{1..2} = {2}", expression };
	expect_bool_value(expression.expression, false);

	Expression_Runner test3 { "{1..2} # {2,1}", expression };
	expect_bool_value(expression.expression, false);

	Expression_Runner test4 { "{1..2} # {2}", expression };
	expect_bool_value(expression.expression, true);

	Expression_Runner test5 { "2 IN {0..3}", expression };
	expect_bool_value(expression.expression, true);

	Expression_Runner test6 { "4 IN {0..3}", expression };
	expect_bool_value(expression.expression, false);
}

TEST(Expression_Tests, invalid) {
	Context context;
	sema::Expression expression { context };
	Expression_Runner test1 { "}", expression, true, true };
}