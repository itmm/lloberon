#include "parser-tests.h"

using Element_Runner = Parser_Value_Runner<
	expr::Const_Ptr, &Parser::parse_element
>;

TEST(Element_Tests, empty) {
	context::clear();
	expr::Const_Ptr value;
	Element_Runner test1 { "", value, true };
}

TEST(Element_Tests, simple) {
	context::clear();
	expr::Const_Ptr value;
	value = expr::Const::create(0U);
	Element_Runner test1 { "3", value };
	EXPECT_TRUE(value->is_set());
	EXPECT_EQ(value->set_value(), 0x00000008);
}

TEST(Element_Tests, range) {
	context::clear();
	expr::Const_Ptr value;
	value = expr::Const::create(0U);
	Element_Runner test1 { "3..6", value };
	EXPECT_TRUE(value->is_set());
	EXPECT_EQ(value->set_value(), 0x00000078);
}

TEST(Element_Tests, incomplete) {
	context::clear();
	expr::Const_Ptr value;
	value = expr::Const::create(0U);
	Element_Runner test1 { "3..", value, true };
}