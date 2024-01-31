#include "parser-tests.h"

using Var_Declaration_Runner = Parser_No_Arg_Void_Runner<
	&Parser::parse_variable_declaration
>;

TEST(Var_Declaration_Tests, empty) {
	Var_Declaration_Runner test1 { "", true };
}

TEST(Var_Declaration_Tests, simple) {
	context::scope->register_base_types();
	Var_Declaration_Runner test1 { "a*: INTEGER" };
	context::clear();
}

TEST(Var_Declaration_Tests, incomplete) {
	Var_Declaration_Runner test1 { "a:", true };
	context::scope->clear();

	Var_Declaration_Runner test2 { "a", true };
	context::clear();
}

TEST(Var_Declaration_Tests, invalid) {
	context::scope->register_base_types();
	Var_Declaration_Runner test1 { "a INTEGER", true, true };
	context::scope->clear();

	Var_Declaration_Runner test2 { "a;", true, true };
	context::clear();
}