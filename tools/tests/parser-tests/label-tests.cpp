#include "parser-tests.h"
#include "type/type.h"
#include "const-tests.h"

using Const_Label_Runner = Parser_Value_Runner<
	sema::Const_Label, &Parser::parse_label
>;

TEST(Label_Tests, empty) {
	Context context;
	sema::Const_Label const_label { context };
	Const_Label_Runner test1 { "", const_label, true };
}

TEST(Label_Tests, simple) {
	Context context;
	sema::Const_Label label { context };
	Const_Label_Runner test1 { "3", label };
	expect_int_value(label.value, 3);

	Const_Label_Runner test2 { "\"abc\"", label };
	expect_string_value(label.value, "abc");
}
