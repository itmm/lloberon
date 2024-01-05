#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using For_Statement_Runner = Parser_Value_Runner<
    lloberon::sema::For_Statement, &lloberon::Parser::parse_for_statement
>;

TEST(For_Statement_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::For_Statement for_statement { scope };
    For_Statement_Runner("", for_statement, true);
}

TEST(For_Statement_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "x", nullptr
    });
    lloberon::sema::For_Statement for_statement { scope };
    For_Statement_Runner("FOR a := 1 TO 3 DO x := x + a END", for_statement);
}

TEST(For_Statement_Tests, with_step) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "x", nullptr
    });
    lloberon::sema::For_Statement for_statement { scope };
    For_Statement_Runner("FOR a := 1 TO 10 BY 2 DO x := x + a END", for_statement);
}

TEST(For_Statement_Tests, with_stepdown) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "x", nullptr
    });
    lloberon::sema::For_Statement for_statement { scope };
    For_Statement_Runner("FOR a := 10 TO 0 BY -2 DO x := x + a END", for_statement);
}

TEST(For_Statement_Tests, wrong) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    lloberon::sema::For_Statement for_statement { scope };
    For_Statement_Runner("FOR", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR a", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR :=", for_statement, true, true);

    for_statement.clear();
    For_Statement_Runner("FOR a :=", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR a 1", for_statement, true, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1 TO", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1 TO 10", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1 10", for_statement, true, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1 TO 10 DO", for_statement, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1 TO 10 END", for_statement, true, true);

    for_statement.clear();
    For_Statement_Runner("FOR a := 1 TO 10 BY DO", for_statement, true);
}

#pragma clang diagnostic pop