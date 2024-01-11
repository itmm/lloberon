#include "parser-tests.h"
#include "decl/variable.h"
#include "expr/expression.h"

using Expression_Runner = Parser_Value_Runner<
	sema::Expression, &Parser::parse_expression
>;

TEST(Expression_Tests, empty) {
	Scope scope;
	sema::Expression expression { scope };
	Expression_Runner test1 { "", expression, true };
}

TEST(Expression_Tests, single) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("b", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Expression expression { scope };
	Expression_Runner test1 { "3 = 4", expression };

	expression.clear();
	Expression_Runner test2 { "3 # 4", expression };

	expression.clear();
	Expression_Runner test3 { "3 < 4", expression };

	expression.clear();
	Expression_Runner test4 { "3 <= 4", expression };

	expression.clear();
	Expression_Runner test5 { "3 > 4", expression };

	expression.clear();
	Expression_Runner test6 { "3 >= 4", expression };

	expression.clear();
	Expression_Runner test7 { "3 IN a", expression };

	expression.clear();
	Expression_Runner test8 { "a IS b", expression };

	expression.clear();
	Expression_Runner test9 { "NIL", expression };
	EXPECT_EQ(expression.expression, expr::Expression::nil);
}

TEST(Expression_Tests, multiple) {
	Scope scope;
	sema::Expression expression { scope };
	Expression_Runner test1 { "3 < 4 = TRUE", expression };
}

TEST(Expression_Tests, invalid) {
	Scope scope;
	sema::Expression expression { scope };
	Expression_Runner test1 { "}", expression, true, true };
}