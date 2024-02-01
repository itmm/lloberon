#include "parser-tests.h"
#include "import-tests.h"

#include "decl/declaration.h"

using Import_Runner = Parser_Arg_Void_Runner<Scope, &Parser::parse_import>;

TEST(Import_Tests, empty) {
	Scope scope;
	Import_Runner test1 { "", scope, true };
	expect_no_modules(scope);
}

TEST(Import_Tests, simple) {
	Scope scope;
	Import_Runner test1 { "Out", scope };
	expect_module(scope, "Out", "Out");
	scope.clear();

	Import_Runner test2 { "a := Out", scope };
	expect_module(scope, "a", "Out");
}

TEST(Import_Tests, missing) {
	Scope scope;
	Import_Runner test1 { "Out SYSTEM", scope, false, true };
	expect_module(scope, "Out", "Out");
	scope.clear();

	Import_Runner test2 { "a :=", scope, true };
	expect_no_modules(scope);
}