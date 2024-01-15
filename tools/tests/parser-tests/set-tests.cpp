#include "parser-tests.h"

using Set_Runner = Parser_Value_Runner<
	sema::Const_Expression, &Parser::parse_set
>;

TEST(Set_Tests, empty) {
	Context context;
	sema::Const_Expression expression { context };
	Set_Runner test1 { "", expression, true };
	Set_Runner test2 { "{}", expression };
	EXPECT_EQ(expression.expression->set_value(), 0x0000u);
}

TEST(Set_Tests, simple) {
	Context context;
	sema::Const_Expression expression { context };
	Set_Runner test1 { "{1}", expression };
	EXPECT_EQ(expression.expression->set_value(), 0x00002u);

	Set_Runner test2 { "{1, 2, 3}", expression };
	EXPECT_EQ(expression.expression->set_value(), 0x000eu);
}

TEST(Set_Tests, ranges) {
	Context context;
	sema::Const_Expression expression { context };
	Set_Runner test1 { "{1..2}", expression };
	EXPECT_EQ(expression.expression->set_value(), 0x0006u);

	Set_Runner test2 { "{1..2, 4..6}", expression };
	EXPECT_EQ(expression.expression->set_value(), 0x0076u);
}

TEST(Set_Tests, incomplete) {
	Context context;
	sema::Const_Expression expression { context };
	Set_Runner test1 { "{1..3", expression, true };
	Set_Runner test2 { "{1..}", expression, true, true };
	Set_Runner test3 { "{1,}", expression, true, true };
	Set_Runner test4 { "{1,,", expression, true, true };
}