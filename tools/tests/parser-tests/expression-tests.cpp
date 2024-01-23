#include "parser-tests.h"
#include "expr/expression.h"
#include "expr/variable.h"
#include "const-tests.h"

using Expression_Runner = Parser_No_Void_Runner<
	expr::Expression_Ptr, &Parser::parse_expression
>;

TEST(Expression_Tests, empty) {
	Expression_Runner test1 { "",  true };
}

TEST(Expression_Tests, single) {
	context::scope->register_base_types();
	Expression_Runner test1 { "3 = 4" };
	expect_bool_value(test1.value, false);

	Expression_Runner test2 { "3 # 4" };
	expect_bool_value(test2.value, true);

	Expression_Runner test3 { "3 < 4" };
	expect_bool_value(test3.value, true);

	Expression_Runner test4 { "3 <= 4" };
	expect_bool_value(test4.value, true);

	Expression_Runner test5 { "3 > 4" };
	expect_bool_value(test5.value, false);

	Expression_Runner test6 { "3 >= 4" };
	expect_bool_value(test6.value, false);

	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	Expression_Runner test7 { "3 IN a" };
	Expression_Runner test8 { "a IS INTEGER" };
	Expression_Runner test9 { "NIL" };
	EXPECT_EQ(test9.value, expr::Expression::nil);
	context::clear();
}

TEST(Expression_Tests, multiple) {
	Expression_Runner test1 { "3 < 4 = TRUE" };
	expect_bool_value(test1.value, true);
}

TEST(Expression_Tests, set) {
	Expression_Runner test1 { "{1..2} = {2,1}" };
	expect_bool_value(test1.value, true);

	Expression_Runner test2 { "{1..2} = {2}" };
	expect_bool_value(test2.value, false);

	Expression_Runner test3 { "{1..2} # {2,1}" };
	expect_bool_value(test3.value, false);

	Expression_Runner test4 { "{1..2} # {2}" };
	expect_bool_value(test4.value, true);

	Expression_Runner test5 { "2 IN {0..3}" };
	expect_bool_value(test5.value, true);

	Expression_Runner test6 { "4 IN {0..3}" };
	expect_bool_value(test6.value, false);
}

TEST(Expression_Tests, invalid) {
	Expression_Runner test1 { "}", true, true };
}