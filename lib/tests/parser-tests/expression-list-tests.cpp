#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Expression_List_Runner = Parser_Value_Runner<lloberon::sema::Expression_List, &lloberon::Parser::parse_expression_list>;

TEST(Expression_List_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Expression_List expression_list { scope };
    Expression_List_Runner("", expression_list, true);
}

TEST(Expression_List_Tests, single) {
    lloberon::Scope scope;
    lloberon::sema::Expression_List expression_list { scope };
    Expression_List_Runner("3", expression_list);
}

TEST(Expression_List_Tests, multiple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration{
        nullptr, {}, "f", nullptr
    });
    lloberon::sema::Expression_List expression_list { scope };
    Expression_List_Runner("f(3, 4), 4", expression_list);
}

TEST(Expression_List_Tests, incomplete) {
    lloberon::Scope scope;
    lloberon::sema::Expression_List expression_list { scope };
    Expression_List_Runner(",", expression_list, true);

    expression_list.clear();
    Expression_List_Runner("3,", expression_list, true);
}

#pragma clang diagnostic pop