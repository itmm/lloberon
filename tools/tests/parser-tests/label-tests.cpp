#include "decl/type.h"
#include "parser-tests.h"
#include "type/type.h"
#include "const-tests.h"

using Const_Label_Runner = Parser_Value_Runner<
	sema::Const_Label, &Parser::parse_label
>;
using Type_Label_Runner = Parser_Value_Runner<
	sema::Type_Label, &Parser::parse_label
>;

TEST(Label_Tests, empty) {
	Scope scope;
	sema::Const_Label const_label { scope };
	Const_Label_Runner test1 { "", const_label, true };

	sema::Type_Label type_label { scope };
	Type_Label_Runner test2 { "", type_label, true };
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

TEST(Label_Tests, qual_ident) {
	Scope scope;
	decl::Type::register_base_types(scope);
	auto module { std::make_shared<decl::Module>("X") };
	module->insert("Byte", std::make_shared<decl::Type>(
		type::Type::base_byte
	));
	scope.insert("X", module);
	sema::Type_Label label { scope };
	Type_Label_Runner test1 { "INTEGER", label };

	label.clear();
	Type_Label_Runner test2 { "X.Byte", label };
}

TEST(Label_Tests, wrong) {
	Scope scope;
	auto module { std::make_shared<decl::Module>("X") };
	scope.insert("X", module);
	sema::Type_Label label { scope };
	Type_Label_Runner test1 { "X.", label, true };

	label.clear();
	Type_Label_Runner test2 { "NIL", label, true, true };
}