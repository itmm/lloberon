#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Simple_Expression_Runner = Parser_Value_Runner<lloberon::sema::Simple_Expression, &Parser::parse_simple_expression>;

TEST(Simple_Expression_Tests, empty) {
    Scope scope;
    lloberon::sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner("", simple_expression, true);
}

TEST(Simple_Expression_Tests, single) {
    Scope scope;
    lloberon::sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner("3", simple_expression);
}

TEST(Simple_Expression_Tests, simple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
        nullptr, {}, "b", nullptr
    });
    lloberon::sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner("3 + 4", simple_expression);

    simple_expression.clear();
    Simple_Expression_Runner("3 - 4", simple_expression);

    simple_expression.clear();
    Simple_Expression_Runner("a OR b", simple_expression);
}

TEST(Simple_Expression_Tests, factor) {
    Scope scope;
    lloberon::sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner("3 * 4", simple_expression);

    simple_expression.clear();
    Simple_Expression_Runner("3 / 2 + 4 * 3", simple_expression);
}

TEST(Simple_Expression_Tests, unaries) {
    Scope scope;
    lloberon::sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner("+3", simple_expression);

    simple_expression.clear();
    Simple_Expression_Runner("-3 + 4", simple_expression);

    simple_expression.clear();
    Simple_Expression_Runner("+-3", simple_expression, true, true);
}

TEST(Simple_Expression_Tests, incomplete) {
    Scope scope;
    lloberon::sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner("3 +", simple_expression, true);

    simple_expression.clear();
    Simple_Expression_Runner("+", simple_expression, true);
}

#pragma clang diagnostic pop