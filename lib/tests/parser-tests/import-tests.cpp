#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"
#include "import-tests.h"

#include "sema/declaration.h"

using Import_Runner = Parser_Value_Runner<Scope, &Parser::parse_import>;

TEST(Import_Tests, empty) {
    Scope scope;
    Import_Runner("", scope, true);
    expect_no_modules(scope);
}

TEST(Import_Tests, simple) {
    Scope scope;
    Import_Runner("a", scope);
    expect_module(scope, "a", "a");

    new (&scope) Scope { };
    Import_Runner("a := b", scope);
    expect_module(scope, "a", "b");
}

TEST(Import_Tests, missing) {
    Scope scope;
    Import_Runner("a b", scope, false, true);
    expect_module(scope, "a", "a");

    new (&scope) Scope { };
    Import_Runner("a :=", scope, true);
    expect_no_modules(scope);
}

#pragma clang diagnostic pop