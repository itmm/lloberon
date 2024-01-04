#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"
#include "import-tests.h"

#include "lloberon/ast/declaration.h"

using Import_Runner = Parser_Value_Runner<lloberon::Scope, &lloberon::Parser::parse_import>;

TEST(Import_Tests, empty) {
    lloberon::Scope scope;
    Import_Runner("", scope, true);
    expect_no_modules(scope);
}

TEST(Import_Tests, simple) {
    lloberon::Scope scope;
    Import_Runner("a", scope);
    expect_module(scope, "a", "a");

    new (&scope) lloberon::Scope { };
    Import_Runner("a := b", scope);
    expect_module(scope, "a", "b");
}

TEST(Import_Tests, missing) {
    lloberon::Scope scope;
    Import_Runner("a b", scope, false, true);
    expect_module(scope, "a", "a");

    new (&scope) lloberon::Scope { };
    Import_Runner("a :=", scope, true);
    expect_no_modules(scope);
}

#pragma clang diagnostic pop