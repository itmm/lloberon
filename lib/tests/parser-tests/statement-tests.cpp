#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Statement_Runner = Parser_Value_Runner<
    lloberon::sema::Statement, &lloberon::Parser::parse_statement
>;

TEST(Statement_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Statement statement { scope };
    Statement_Runner("", statement);
}

TEST(Statement_Tests, single) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "b", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "i", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "cond", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "f", nullptr
    });
    lloberon::sema::Statement statement { scope };
    Statement_Runner("a := 3", statement);

    statement.clear();
    Statement_Runner("f(2, 3)", statement);

    statement.clear();
    Statement_Runner("IF b THEN a := 3 END", statement);

    statement.clear();
    Statement_Runner("CASE cond OF 3: a := 3 END", statement);

    statement.clear();
    Statement_Runner("WHILE cond DO END", statement);

    statement.clear();
    Statement_Runner("REPEAT UNTIL cond", statement);

    statement.clear();
    Statement_Runner("FOR i := 1 TO 10 DO END", statement);
}

TEST(Statement_Tests, invalid) {
    lloberon::Scope scope;
    lloberon::sema::Statement statement { scope };
    Statement_Runner("3", statement, false, true);
}

#pragma clang diagnostic pop