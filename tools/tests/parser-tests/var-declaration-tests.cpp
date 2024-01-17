#include "parser-tests.h"
#include "decl/type.h"

using Var_Declaration_Runner = Parser_String_Runner<
	&Parser::parse_variable_declaration
>;

TEST(Var_Declaration_Tests, empty) {
	context::clear();
	Var_Declaration_Runner test1 { "", true };
}

TEST(Var_Declaration_Tests, simple) {
	context::clear();
	decl::Type::register_base_types(*context::scope);
	Var_Declaration_Runner test1 { "a*: INTEGER" };
}

TEST(Var_Declaration_Tests, incomplete) {
	context::clear();
	Var_Declaration_Runner test1 { "a:", true };

	context::scope->clear();
	Var_Declaration_Runner test2 { "a", true };
}

TEST(Var_Declaration_Tests, invalid) {
	context::clear();
	decl::Type::register_base_types(*context::scope);
	Var_Declaration_Runner test1 { "a INTEGER", true, true };

	context::scope->clear();
	Var_Declaration_Runner test2 { "a;", true, true };
}