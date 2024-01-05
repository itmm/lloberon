#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using If_Statement_Runner = Parser_Value_Runner<
    lloberon::sema::If_Statement, &lloberon::Parser::parse_if_statement
>;

TEST(If_Statement_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::If_Statement if_statement { scope };
    If_Statement_Runner("", if_statement, true);
}

TEST(If_Statement_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "b", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "cond", nullptr
    });
    lloberon::sema::If_Statement if_statement { scope };
    If_Statement_Runner("IF cond THEN a := 1; b := TRUE END", if_statement);
}

TEST(If_Statement_Tests, with_else) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "b", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "cond", nullptr
    });
    lloberon::sema::If_Statement if_statement { scope };
    If_Statement_Runner("IF cond THEN a := 1 ELSE a := 2; b := TRUE END", if_statement);
}

TEST(If_Statement_Tests, with_elsif) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    lloberon::sema::If_Statement if_statement { scope };
    If_Statement_Runner(
        "IF a < 3 THEN a := -1 ELSIF a > 3 THEN a := 1 ELSE a := 0 END", if_statement
    );
}

#pragma clang diagnostic pop