#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Repeat_Statement_Runner = Parser_Value_Runner<
    lloberon::sema::Repeat_Statement, &lloberon::Parser::parse_repeat_statement
>;

TEST(Repeat_Statement_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Repeat_Statement repeat_statement { scope };
    Repeat_Statement_Runner("", repeat_statement, true);
}

TEST(Repeat_Statement_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    lloberon::sema::Repeat_Statement repeat_statement { scope };
    Repeat_Statement_Runner("REPEAT a := a + 1 UNTIL a > 10", repeat_statement);
}

#pragma clang diagnostic pop