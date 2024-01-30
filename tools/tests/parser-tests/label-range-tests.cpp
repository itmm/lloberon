#include "parser-tests.h"
#include "const-tests.h"

using Label_Range_Runner = Parser_No_Void_Runner<
	sema::Const_Label_Range, &Parser::parse_label_range
>;

TEST(Label_Range_Tests, empty) {
	Label_Range_Runner test1 { "", true };
}

TEST(Label_Range_Tests, simple) {
	Label_Range_Runner test1 { "3" };
	expect_int_value(test1.value.begin, 3);
	expect_int_value(test1.value.end, 3);

	Label_Range_Runner test2 { "3..5" };
	expect_int_value(test2.value.begin, 3);
	expect_int_value(test2.value.end, 5);
}

TEST(Label_Range_Tests, incomplete) {
	Label_Range_Runner test1 { "3..", true };
}