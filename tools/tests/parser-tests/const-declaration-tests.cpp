#include "parser-tests.h"
#include "decl/const.h"
#include "expr/const.h"
#include "const-tests.h"

using Const_Declaration_Runner = Parser_Value_Runner<
	Context, &Parser::parse_const_declaration
>;

TEST(Const_Declaration_Tests, empty) {
	Context context;
	Const_Declaration_Runner test1 { "", context, true };
}

TEST(Const_Decalaration_Tests, simple) {
	Context context;
	Const_Declaration_Runner test1 { "a* = 3 + 4", context };
	auto entry { std::dynamic_pointer_cast<decl::Const>(context.scope->lookup("a")) };
	EXPECT_NE(entry, nullptr);
	if (entry) { expect_int_value(entry->value, 7); }
}

TEST(Const_Declaration_Tests, incomplete) {
	Context context;
	Const_Declaration_Runner test1 { "a =", context, true };
	Const_Declaration_Runner test2 { "a", context, true };
}