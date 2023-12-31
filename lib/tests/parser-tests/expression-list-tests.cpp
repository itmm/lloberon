#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Expression_List_Runner = Parser_String_Runner<&lloberon::Parser::parse_expression_list>;

TEST(Expression_List_Tests, empty) {
    Expression_List_Runner("", true);
}

TEST(Expression_List_Tests, single) {
    Expression_List_Runner("3");
}

TEST(Expression_List_Tests, multiple) {
    Expression_List_Runner("f(3, 4), 4");
}

TEST(Expression_List_Tests, incomplete) {
    Expression_List_Runner(",", true);
    Expression_List_Runner("3,", true);
}

#pragma clang diagnostic pop