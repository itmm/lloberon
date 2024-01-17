#include "parser-tests.h"

using Length_Runner = Parser_Value_Runner<sema::Length, &Parser::parse_length>;

TEST(Length_Tests, empty) {
	context::clear();
	sema::Length expression;
	Length_Runner test1 { "", expression, true };
}

TEST(Length_Tests, simple) {
	context::clear();
	sema::Length expression;
	Length_Runner test2 { "3", expression };
	EXPECT_EQ(expression.length, 3);
}