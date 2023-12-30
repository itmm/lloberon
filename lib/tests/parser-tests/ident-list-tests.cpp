#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Ident_List_Runner = Parser_String_Runner<&lloberon::Parser::parse_ident_list>;

TEST(Ident_List_Tests, empty) {
    Ident_List_Runner("", true);
}

TEST(Ident_List_Tests, single) {
    Ident_List_Runner("abc");
    Ident_List_Runner("abc*");
}

TEST(Identlist_Tests, multiple) {
    Ident_List_Runner("a, b*, c");
    Ident_List_Runner("a*, b, c*");
    Ident_List_Runner("a, b");
    Ident_List_Runner("a*, b*");
}

TEST(Identlist_Tests, empty_items) {
    Ident_List_Runner("a,", true);
    Ident_List_Runner(",", true, true);
    Ident_List_Runner("a,,b", true, true);
}

TEST(Identlist_Tests, wrong_items) {
    Ident_List_Runner("1", true, true);
    Ident_List_Runner("a,2", true, true);
}

#pragma clang diagnostic pop