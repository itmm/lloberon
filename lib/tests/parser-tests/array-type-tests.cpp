#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Array_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_array_type>;

TEST(Array_Type_Tests, empty) {
    Array_Type_Runner("", true);
}

TEST(Array_Type_Tests, simple) {
    Array_Type_Runner("ARRAY 3 OF BYTE");
}

TEST(Array_Type_Tests, multiple) {
    Array_Type_Runner("ARRAY 3, 3 OF BYTE");
}

TEST(Array_Type_Tests, cascading) {
    Array_Type_Runner ("ARRAY 3 OF ARRAY 3 OF BYTE");
}

#pragma clang diagnostic pop