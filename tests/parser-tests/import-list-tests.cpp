#include "parser-tests.h"
#include "import-tests.h"

using Import_List_Runner = Parser_Arg_Void_Runner<
	Scope, &Parser::parse_import_list
>;

TEST(Import_List_Tests, empty) {
	Scope scope;
	Import_List_Runner test1 { "", scope, true };
	expect_no_modules(scope);
}

TEST(Import_List_Tests, simple) {
	Scope scope;
	Import_List_Runner test1 { "IMPORT SYSTEM;", scope };
	expect_module(scope, "SYSTEM", "SYSTEM");
	scope.clear();

	Import_List_Runner test2 { "IMPORT Out, SYSTEM;", scope };
	expect_module(scope, "Out", "Out");
	expect_module(scope, "SYSTEM", "SYSTEM");
	scope.clear();

	Import_List_Runner test3 { "IMPORT a := Out, SYSTEM;", scope };
	expect_module(scope, "a", "Out");
	expect_module(scope, "SYSTEM", "SYSTEM");
	scope.clear();

	Import_List_Runner test4 { "IMPORT Out, b := SYSTEM;", scope };
	expect_module(scope, "Out", "Out");
	expect_module(scope, "b", "SYSTEM");
	scope.clear();

	Import_List_Runner test5 { "IMPORT a := Out, c := SYSTEM;", scope };
	expect_module(scope, "a", "Out");
	expect_module(scope, "c", "SYSTEM");
}

TEST(Import_List_Tests, missing) {
	Scope scope;
	Import_List_Runner test1 { "IMPORT", scope, true };
	scope.clear();

	Import_List_Runner test2 { "IMPORT Out", scope, true };
	scope.clear();

	Import_List_Runner test3 { "IMPORT Out,", scope, true };
	scope.clear();

	Import_List_Runner test4 { "IMPORT Out, SYSTEM", scope, true };
	scope.clear();

	Import_List_Runner test5 { "IMPORT a :=", scope, true };
	scope.clear();

	Import_List_Runner test6 { "IMPORT a := Out", scope, true };
}