#include "parser-tests.h"

using Set_Runner = Parser_Arg_Void_Runner<expr::Const_Ptr, &Parser::parse_set>;

TEST(Set_Tests, empty) {
	expr::Const_Ptr expression;
	Set_Runner test1 { "", expression, true };
	Set_Runner test2 { "{}", expression };
	EXPECT_EQ(expression->set_value(), 0x0000u);
}

TEST(Set_Tests, simple) {
	expr::Const_Ptr expression;
	Set_Runner test1 { "{1}", expression };
	EXPECT_EQ(expression->set_value(), 0x00002u);

	Set_Runner test2 { "{1, 2, 3}", expression };
	EXPECT_EQ(expression->set_value(), 0x000eu);
}

TEST(Set_Tests, ranges) {
	expr::Const_Ptr expression;
	Set_Runner test1 { "{1..2}", expression };
	EXPECT_EQ(expression->set_value(), 0x0006u);

	Set_Runner test2 { "{1..2, 4..6}", expression };
	EXPECT_EQ(expression->set_value(), 0x0076u);
}

TEST(Set_Tests, incomplete) {
	expr::Const_Ptr expression;
	Set_Runner test1 { "{1..3", expression, true };
	Set_Runner test2 { "{1..}", expression, true, true };
	Set_Runner test3 { "{1,}", expression, true, true };
	Set_Runner test4 { "{1,,", expression, true, true };
}