#include "parser-tests.h"
#include "const-tests.h"

using Label_Range_Runner = Parser_Value_Runner<
	sema::Const_Label_Range, &Parser::parse_label_range
>;

TEST(Label_Range_Tests, empty) {
	sema::Const_Label_Range range;
	Label_Range_Runner test1 { "", range, true };
}

TEST(Label_Range_Tests, simple) {
	sema::Const_Label_Range range;
	Label_Range_Runner test1 { "3", range };
	expect_int_value(range.begin, 3);
	expect_int_value(range.end, 3);

	Label_Range_Runner test2 { "3..5", range };
	expect_int_value(range.begin, 3);
	expect_int_value(range.end, 5);
}

TEST(Label_Range_Tests, incomplete) {
	sema::Const_Label_Range range;
	Label_Range_Runner test1 { "3..", range, true };
}