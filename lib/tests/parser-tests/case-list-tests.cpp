#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Case_List_Runner = Parser_String_Runner<&lloberon::Parser::parse_case_list>;

TEST(Case_List_Tests, empty) {
    Case_List_Runner("", true);
}

TEST(Case_List_Tests, single) {
    Case_List_Runner("3..4");
}

TEST(Case_List_Tests, multiple) {
    Case_List_Runner("3..4, 7..8, 12");
}

TEST(Case_List_Tests, incomplete) {
    Case_List_Runner("3,", true);
}

#pragma clang diagnostic pop