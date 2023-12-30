#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Field_List_Sequence_Runner = Parser_String_Runner<&lloberon::Parser::parse_field_list_sequence>;

TEST(Field_List_Sequence_Tests, empty) {
    Field_List_Sequence_Runner("", true);
}

TEST(Field_List_Sequence_Tests, single) {
    Field_List_Sequence_Runner("a: BYTE");
}

TEST(Field_List_Sequence_Tests, multiple) {
    Field_List_Sequence_Runner("a: BYTE; b: BYTE");
}

TEST(Field_List_Sequence_Tests, incomplete) {
    Field_List_Sequence_Runner("a: BYTE;", true);
}

#pragma clang diagnostic pop