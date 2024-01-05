#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"
#include "import-tests.h"

using Import_List_Runner = Parser_Value_Runner<
    Scope, &Parser::parse_import_list
>;

TEST(Import_List_Tests, empty) {
    Scope scope;
    Import_List_Runner("", scope, true);
    expect_no_modules(scope);
}

TEST(Import_List_Tests, simple) {
    Scope scope;
    Import_List_Runner("IMPORT a;", scope);
    expect_module(scope, "a", "a");

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a, b;", scope);
    expect_module(scope, "a", "a");
    expect_module(scope, "b", "b");

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a := b, c;", scope);
    expect_module(scope, "a", "b");
    expect_module(scope, "c", "c");

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a, b := c;", scope);
    expect_module(scope, "a", "a");
    expect_module(scope, "b", "c");

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a := b, c := d;", scope);
    expect_module(scope, "a", "b");
    expect_module(scope, "c", "d");
}

TEST(Import_List_Tests, missing) {
    Scope scope;
    Import_List_Runner("IMPORT", scope, true);
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a", scope, true);
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a,", scope, true);
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a, b", scope, true);
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a :=", scope, true);
    expect_no_modules(scope);

    new (&scope) Scope { };
    Import_List_Runner("IMPORT a := b", scope, true);
    expect_no_modules(scope);
}

#pragma clang diagnostic pop