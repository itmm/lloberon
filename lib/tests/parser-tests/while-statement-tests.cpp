#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using While_Statement_Runner = Parser_Value_Runner<
    sema::While_Statement, &Parser::parse_while_statement
>;

TEST(While_Statement_Tests, empty) {
    Scope scope;
    sema::While_Statement while_statement { scope };
    While_Statement_Runner("", while_statement, true);
}

TEST(While_Statement_Tests, simple) {
    Scope scope;
    scope.insert(new Variable_Declaration{
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration{
        nullptr, {}, "INC", nullptr
    });
    sema::While_Statement while_statement { scope };
    While_Statement_Runner("WHILE a < 3 DO INC(a) END", while_statement);
}

TEST(While_Statement_Tests, with_elsif) {
    Scope scope;
    scope.insert(new Variable_Declaration{
        nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration{
        nullptr, {}, "b", nullptr
    });
    scope.insert(new Variable_Declaration{
        nullptr, {}, "c", nullptr
    });
    scope.insert(new Variable_Declaration{
        nullptr, {}, "INC", nullptr
    });
    sema::While_Statement while_statement { scope };
    While_Statement_Runner(
        "WHILE a < 3 DO INC(a) ELSIF b < 3 DO INC(b) ELSIF c < 3 DO INC(c) END",
        while_statement
    );
}

TEST(While_Statement_Tests, wrong) {
    Scope scope;
    scope.insert(new Variable_Declaration{
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration{
            nullptr, {}, "INC", nullptr
    });
    sema::While_Statement while_statement { scope };
    While_Statement_Runner("WHILE DO", while_statement, true);

    while_statement.clear();
    While_Statement_Runner("WHILE a < 3 DO INC(a)", while_statement, true);

    while_statement.clear();
    While_Statement_Runner("WHILE a ELSIF", while_statement, true, true);

    while_statement.clear();
    While_Statement_Runner("WHILE a < 3 DO ELSIF END", while_statement, true);
}

#pragma clang diagnostic pop