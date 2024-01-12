#include "parser-tests.h"
#include "decl/type.h"

using Var_Declaration_Runner = Parser_Value_Runner<
	Scope, &Parser::parse_variable_declaration
>;

TEST(Var_Declaration_Tests, empty) {
	Scope scope;
	Var_Declaration_Runner test1 { "", scope, true };
}

TEST(Var_Declaration_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	Var_Declaration_Runner test1 { "a*: INTEGER", scope };
}

TEST(Var_Declaration_Tests, incomplete) {
	Scope scope;
	Var_Declaration_Runner test1 { "a:", scope, true };

	scope.clear();
	Var_Declaration_Runner test2 { "a", scope, true };
}

TEST(Var_Declaration_Tests, invalid) {
	Scope scope;
	decl::Type::register_base_types(scope);
	Var_Declaration_Runner test1 { "a INTEGER", scope, true, true };

	scope.clear();
	Var_Declaration_Runner test2 { "a;", scope, true, true };
}