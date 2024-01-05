#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Expression_Runner = Parser_Value_Runner<
    sema::Expression, &Parser::parse_expression
>;

TEST(Expression_Tests, empty) {
    Scope scope;
    sema::Expression expression { scope };
    Expression_Runner("", expression, true);
}

TEST(Expression_Tests, single) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
        nullptr, {}, "b", nullptr
    });
    sema::Expression expression { scope };
    Expression_Runner("3 = 4", expression);

    expression.clear();
    Expression_Runner("3 # 4", expression);

    expression.clear();
    Expression_Runner("3 < 4", expression);

    expression.clear();
    Expression_Runner("3 <= 4", expression);

    expression.clear();
    Expression_Runner("3 > 4", expression);

    expression.clear();
    Expression_Runner("3 >= 4", expression);

    expression.clear();
    Expression_Runner("3 IN a", expression);

    expression.clear();
    Expression_Runner("a IS b", expression);
}

TEST(Expression_Tests, multiple) {
    Scope scope;
    sema::Expression expression { scope };
    Expression_Runner("3 < 4 = TRUE", expression);
}

TEST(Expression_Tests, invalid) {
    Scope scope;
    sema::Expression expression { scope };
    Expression_Runner("}", expression, true);
}

#pragma clang diagnostic pop