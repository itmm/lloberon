#include "parser-tests.h"
#include "type/type.h"
#include "const-tests.h"

using Const_Label_Runner = Parser_Value_Runner<
	expr::Const_Ptr, &Parser::parse_label
>;

TEST(Label_Tests, empty) {
	context::clear();
	expr::Const_Ptr const_label;
	Const_Label_Runner test1 { "", const_label, true };
}

TEST(Label_Tests, simple) {
	context::clear();
	expr::Const_Ptr label;
	Const_Label_Runner test1 { "3", label };
	expect_int_value(label, 3);

	Const_Label_Runner test2 { "\"abc\"", label };
	expect_string_value(label, "abc");
}
