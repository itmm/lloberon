#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Field_List_Runner = Parser_String_Runner<&lloberon::Parser::parse_field_list>;

TEST(Field_List_Tests, empty) {
    Field_List_Runner("", true);
}

TEST(Field_List_Tests, simple) {
    Field_List_Runner("a: INTEGER");
}

TEST(Field_List_Tests, exported) {
    Field_List_Runner("a*: INTEGER");
}

TEST(Field_List_Tests, multiple) {
    Field_List_Runner("a, b: INTEGER");
}

TEST(Field_List_Tests, incomplete) {
    Field_List_Runner("a:", true);
    Field_List_Runner("a INTEGER", true, true);
    Field_List_Runner("a,:", true, true);
}

#pragma clang diagnostic pop