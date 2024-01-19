#include "parser-tests.h"

using Length_Runner = Parser_Value_Runner<int, &Parser::parse_length>;

TEST(Length_Tests, empty) {
	int length;
	Length_Runner test1 { "", length, true };
}

TEST(Length_Tests, simple) {
	int length;
	Length_Runner test2 { "3", length };
	EXPECT_EQ(length, 3);
}