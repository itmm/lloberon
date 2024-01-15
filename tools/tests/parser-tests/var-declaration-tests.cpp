#include "parser-tests.h"
#include "decl/type.h"

using Var_Declaration_Runner = Parser_Value_Runner<
	Context, &Parser::parse_variable_declaration
>;

TEST(Var_Declaration_Tests, empty) {
	Context context;
	Var_Declaration_Runner test1 { "", context, true };
}

TEST(Var_Declaration_Tests, simple) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	Var_Declaration_Runner test1 { "a*: INTEGER", context };
}

TEST(Var_Declaration_Tests, incomplete) {
	Context context;
	Var_Declaration_Runner test1 { "a:", context, true };

	context.scope->clear();
	Var_Declaration_Runner test2 { "a", context, true };
}

TEST(Var_Declaration_Tests, invalid) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	Var_Declaration_Runner test1 { "a INTEGER", context, true, true };

	context.scope->clear();
	Var_Declaration_Runner test2 { "a;", context, true, true };
}