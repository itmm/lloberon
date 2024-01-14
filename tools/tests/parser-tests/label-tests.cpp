#include "decl/type.h"
#include "parser-tests.h"
#include "type/type.h"
#include "const-tests.h"

using Const_Label_Runner = Parser_Value_Runner<
	sema::Const_Label, &Parser::parse_label
>;

TEST(Label_Tests, empty) {
	Scope scope;
	sema::Const_Label const_label { scope };
	Const_Label_Runner test1 { "", const_label, true };
}

TEST(Label_Tests, simple) {
	Scope scope;
	sema::Const_Label label { scope };
	Const_Label_Runner test1 { "3", label };
	expect_int_value(label.value, 3);

	label.clear();
	Const_Label_Runner test2 { "\"abc\"", label };
	expect_string_value(label.value, "abc");
}
