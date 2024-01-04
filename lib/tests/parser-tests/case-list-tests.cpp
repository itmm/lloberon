#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Case_List_Runner = Parser_Value_Runner<
    lloberon::sema::Case_List, &lloberon::Parser::parse_case_list
>;

TEST(Case_List_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Case_List case_list { scope };
    Case_List_Runner("", case_list, true);
}

TEST(Case_List_Tests, single) {
    lloberon::Scope scope;
    lloberon::sema::Case_List case_list { scope };
    Case_List_Runner("3..4", case_list);
}

TEST(Case_List_Tests, multiple) {
    lloberon::Scope scope;
    lloberon::sema::Case_List case_list { scope };
    Case_List_Runner("3..4, 7..8, 12", case_list);
}

TEST(Case_List_Tests, incomplete) {
    lloberon::Scope scope;
    lloberon::sema::Case_List case_list { scope };
    Case_List_Runner("3,", case_list, true);
}

#pragma clang diagnostic pop