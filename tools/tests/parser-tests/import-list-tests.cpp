#include "parser-tests.h"
#include "import-tests.h"

using Import_List_Runner = Parser_Value_Runner<
    Scope, &Parser::parse_import_list
>;

TEST(Import_List_Tests, empty) {
    Scope scope;
    Import_List_Runner test1 { "", scope, true };
    expect_no_modules(scope);
}

TEST(Import_List_Tests, simple) {
    Scope scope;
    Import_List_Runner test1 { "IMPORT a;", scope };
    expect_module(scope, "a", "a");

    new (&scope) Scope { };
    Import_List_Runner test2 { "IMPORT a, b;", scope };
    expect_module(scope, "a", "a");
    expect_module(scope, "b", "b");

    new (&scope) Scope { };
    Import_List_Runner test3 { "IMPORT a := b, c;", scope };
    expect_module(scope, "a", "b");
    expect_module(scope, "c", "c");

    new (&scope) Scope { };
    Import_List_Runner test4 { "IMPORT a, b := c;", scope };
    expect_module(scope, "a", "a");
    expect_module(scope, "b", "c");

    new (&scope) Scope { };
    Import_List_Runner test5 { "IMPORT a := b, c := d;", scope };
    expect_module(scope, "a", "b");
    expect_module(scope, "c", "d");
}

TEST(Import_List_Tests, missing) {
    Scope scope;
    Import_List_Runner test1 { "IMPORT", scope, true };
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner test2 { "IMPORT a", scope, true };
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner test3 { "IMPORT a,", scope, true };
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner test4 { "IMPORT a, b", scope, true };
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner test5 { "IMPORT a :=", scope, true };
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner test6 { "IMPORT a := b", scope, true };
    expect_no_modules(scope);
}