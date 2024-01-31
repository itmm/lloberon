#include "parser-tests.h"

using Element_Runner = Parser_Arg_Void_Runner<
	unsigned, &Parser::parse_element
>;

TEST(Element_Tests, empty) {
	unsigned value;
	Element_Runner test1 { "", value, true };
}

TEST(Element_Tests, simple) {
	unsigned value { 0U };
	Element_Runner test1 { "3", value };
	EXPECT_EQ(value, 0x00000008U);
}

TEST(Element_Tests, range) {
	unsigned value { 0U };
	Element_Runner test1 { "3..6", value };
	EXPECT_EQ(value, 0x00000078U);
}

TEST(Element_Tests, incomplete) {
	unsigned value { 0U };
	Element_Runner test1 { "3..", value, true };
}