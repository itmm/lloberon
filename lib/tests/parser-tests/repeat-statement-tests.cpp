#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Repeat_Statement_Runner = Parser_Value_Runner<
    sema::Repeat_Statement, &Parser::parse_repeat_statement
>;

TEST(Repeat_Statement_Tests, empty) {
    Scope scope;
    sema::Repeat_Statement repeat_statement { scope };
    Repeat_Statement_Runner("", repeat_statement, true);
}

TEST(Repeat_Statement_Tests, simple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    sema::Repeat_Statement repeat_statement { scope };
    Repeat_Statement_Runner("REPEAT a := a + 1 UNTIL a > 10", repeat_statement);
}

#pragma clang diagnostic pop