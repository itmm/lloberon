#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

#include "ident-list-tests.h"

using Ident_List_Runner = Parser_Value_Runner<
    lloberon::sema::Ident_List, &lloberon::Parser::parse_ident_list
>;

TEST(Ident_List_Tests, empty) {
    lloberon::sema::Ident_List list; list.emplace_back("x");
    Ident_List_Runner("", list, true);
    expect_empty_ident_list(list);
}

TEST(Ident_List_Tests, single) {
    lloberon::sema::Ident_List list; list.emplace_back("x");
    Ident_List_Runner("abc", list);
    expect_ident_list(list, "abc", false);
    Ident_List_Runner("abc*", list);
    expect_ident_list(list, "abc", true);
}

TEST(Identlist_Tests, multiple) {
    lloberon::sema::Ident_List list; list.emplace_back("x");
    Ident_List_Runner("a, b*, c", list);
    expect_ident_list(
        list, "a", false, "b", true,
        "c", false
    );
    Ident_List_Runner("d*, e, f*", list);
    expect_ident_list(
        list, "d", true, "e", false,
        "f", true
    );
    Ident_List_Runner("a, b", list);
    expect_ident_list(list, "a", false, "b", false);
    Ident_List_Runner("c*, d*", list);
    expect_ident_list(list, "c", true, "d", true);
}

TEST(Identlist_Tests, empty_items) {
    lloberon::sema::Ident_List list; list.emplace_back("x");
    Ident_List_Runner("a,", list, true);
    expect_empty_ident_list(list);
    list.emplace_back("x");
    Ident_List_Runner(",", list, true, true);
    expect_empty_ident_list(list);
    list.emplace_back("x");
    Ident_List_Runner("a,,b", list, true, true);
    expect_empty_ident_list(list);
}

TEST(Identlist_Tests, wrong_items) {
    lloberon::sema::Ident_List list; list.emplace_back("x");
    Ident_List_Runner("1", list, true, true);
    expect_empty_ident_list(list);
    list.emplace_back("x");
    Ident_List_Runner("a,2", list, true, true);
    expect_empty_ident_list(list);
}

#pragma clang diagnostic pop