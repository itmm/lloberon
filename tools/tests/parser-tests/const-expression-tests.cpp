#include "expr/const.h"
#include "parser-tests.h"
#include "const-tests.h"

using Const_Expression_Runner = Parser_No_Void_Runner<
	expr::Const_Ptr, &Parser::parse_const_expression
>;

TEST(Const_Expression_Tests, empty) {
	Const_Expression_Runner test1 { "", true };
}

TEST(Const_Expression_Tests, literals) {
	Const_Expression_Runner test1 { "234" };
	expect_int_value(test1.value, 234);

	Const_Expression_Runner test2 { "-234" };
	expect_int_value(test2.value, -234);

	Const_Expression_Runner test3 { "2.34" };
	expect_real_value(test3.value, 2.34);

	Const_Expression_Runner test4 { "TRUE" };
	expect_bool_value(test4.value, true);

	Const_Expression_Runner test5 { "FALSE" };
	expect_bool_value(test5.value, false);
}

TEST(Const_Expression_Tests, expressions) {
	Const_Expression_Runner test1 { "3 + 4 * 2" };
	expect_int_value(test1.value, 11);

	Const_Expression_Runner test2 { "2 < 4 # FALSE" };
	expect_bool_value(test2.value, true);

	Const_Expression_Runner test3 { "5 - 3" };
	expect_int_value(test3.value, 2);

	Const_Expression_Runner test4 { "TRUE OR FALSE" };
	expect_bool_value(test4.value, true);
}