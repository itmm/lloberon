#include "parser-tests.h"
#include "decl/const.h"
#include "expr/const.h"
#include "const-tests.h"

using Const_Declaration_Runner = Parser_String_Runner<
	&Parser::parse_const_declaration
>;

TEST(Const_Declaration_Tests, empty) {
	Const_Declaration_Runner test1 { "", true };
}

TEST(Const_Decalaration_Tests, simple) {
	Const_Declaration_Runner test1 { "a* = 3 + 4" };
	auto entry { std::dynamic_pointer_cast<decl::Const>(
		context::scope->lookup("a")
	) };
	EXPECT_NE(entry, nullptr);
	if (entry) { expect_int_value(entry->value, 7); }
	context::clear();
}

TEST(Const_Declaration_Tests, incomplete) {
	Const_Declaration_Runner test1 { "a =", true };
	Const_Declaration_Runner test2 { "a", true };
	context::clear();
}