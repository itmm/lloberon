#include "parser-tests.h"
#include "decl/const.h"
#include "expr/const.h"
#include "const-tests.h"

using Const_Declaration_Runner = Parser_Value_Runner<
	Scope, &Parser::parse_const_declaration
>;

TEST(Const_Declaration_Tests, empty) {
	Scope scope;
	Const_Declaration_Runner test1 { "", scope, true };
}

TEST(Const_Decalaration_Tests, simple) {
	Scope scope;
	Const_Declaration_Runner test1 { "a* = 3 + 4", scope };
	auto entry { std::dynamic_pointer_cast<decl::Const>(scope.lookup("a")) };
	EXPECT_NE(entry, nullptr);
	if (entry) { expect_int_value(entry->value, 7); }
}

TEST(Const_Declaration_Tests, incomplete) {
	Scope scope;
	Const_Declaration_Runner test1 { "a =", scope, true };
	Const_Declaration_Runner test2 { "a", scope, true };
}