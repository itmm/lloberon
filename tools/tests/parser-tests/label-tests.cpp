#include "parser-tests.h"
#include "type/type.h"
#include "const-tests.h"

using Const_Label_Runner = Parser_No_Void_Runner<
	expr::Const_Ptr, &Parser::parse_label
>;

TEST(Label_Tests, empty) {
	Const_Label_Runner test1 { "", true };
}

TEST(Label_Tests, simple) {
	Const_Label_Runner test1 { "3" };
	expect_int_value(test1.value, 3);

	Const_Label_Runner test2 { "\"abc\"" };
	expect_string_value(test2.value, "abc");
}
