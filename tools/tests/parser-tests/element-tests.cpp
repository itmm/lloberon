#include "parser-tests.h"

using Element_Runner = Parser_Value_Runner<sema::Const_Expression, &Parser::parse_element>;

TEST(Element_Tests, empty) {
	Context context;
	sema::Const_Expression value { context };
	Element_Runner test1 { "", value, true };
}

TEST(Element_Tests, simple) {
	Context context;
	sema::Const_Expression value { context };
	value.expression = expr::Const::create(0U);
	Element_Runner test1 { "3", value };
	EXPECT_TRUE(value.expression->is_set());
	EXPECT_EQ(value.expression->set_value(), 0x00000008);
}

TEST(Element_Tests, range) {
	Context context;
	sema::Const_Expression value { context };
	value.expression = expr::Const::create(0U);
	Element_Runner test1 { "3..6", value };
	EXPECT_TRUE(value.expression->is_set());
	EXPECT_EQ(value.expression->set_value(), 0x00000078);
}

TEST(Element_Tests, incomplete) {
	Context context;
	sema::Const_Expression value { context };
	value.expression = expr::Const::create(0U);
	Element_Runner test1 { "3..", value, true };
}