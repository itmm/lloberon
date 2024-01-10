#include "parser-tests.h"

using Const_Expression_Runner = Parser_Value_Runner<sema::Const_Expression, &Parser::parse_const_expression>;

TEST(Const_Expression_Tests, empty) {
    Scope scope;
    sema::Const_Expression expression { scope };
    Const_Expression_Runner("", expression, true);
    // TODO: more tests
}

TEST(Const_Expression_Tests, literals) {
    Scope scope;
    sema::Const_Expression expression { scope };
    // TODO: more tests
    Const_Expression_Runner test1 { "234", expression };

    expression.clear();
    Const_Expression_Runner test2 { "-234", expression };

    expression.clear();
    Const_Expression_Runner test3 { "2.34", expression };

    expression.clear();
    Const_Expression_Runner test4 { "NIL", expression };

    expression.clear();
    Const_Expression_Runner test5 { "TRUE", expression };

    expression.clear();
    Const_Expression_Runner test6 { "FALSE", expression };
}

TEST(Const_Expression_Tests, expressions) {
    Scope scope;
    sema::Const_Expression expression { scope };
    // TODO: more tests
    Const_Expression_Runner test1 { "3 + 4 * 2", expression };

    expression.clear();
    Const_Expression_Runner test2 { "2 < 4 # FALSE", expression };
}