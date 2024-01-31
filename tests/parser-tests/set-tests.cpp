#include "parser-tests.h"

using Set_Runner = Parser_No_Void_Runner<expr::Const_Ptr, &Parser::parse_set>;

TEST(Set_Tests, empty) {
	Set_Runner test1 { "", true };
	Set_Runner test2 { "{}" };
	EXPECT_EQ(test2.value->set_value(), 0x0000u);
}

TEST(Set_Tests, simple) {
	Set_Runner test1 { "{1}" };
	EXPECT_EQ(test1.value->set_value(), 0x00002u);

	Set_Runner test2 { "{1, 2, 3}" };
	EXPECT_EQ(test2.value->set_value(), 0x000eu);
}

TEST(Set_Tests, ranges) {
	Set_Runner test1 { "{1..2}" };
	EXPECT_EQ(test1.value->set_value(), 0x0006u);

	Set_Runner test2 { "{1..2, 4..6}" };
	EXPECT_EQ(test2.value->set_value(), 0x0076u);
}

TEST(Set_Tests, incomplete) {
	Set_Runner test1 { "{1..3", true };
	Set_Runner test2 { "{1..}", true, true };
	Set_Runner test3 { "{1,}", true, true };
	Set_Runner test4 { "{1,,", true, true };
}