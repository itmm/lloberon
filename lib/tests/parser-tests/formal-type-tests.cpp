#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_formal_type>;

TEST(Formal_Type_Tests, empty) {
    Formal_Type_Runner("", true);
}

TEST(Formal_Type_Tests, simple) {
    Formal_Type_Runner("INTEGER");
}

TEST(Formal_Type_Tests, qualified) {
    Formal_Type_Runner("SYSTEM.Byte");
}

TEST(Formal_Type_Tests, array) {
    Formal_Type_Runner("ARRAY OF BYTE");
}

TEST(Formal_Type_Tests, multiple_arrays) {
    Formal_Type_Runner("ARRAY OF ARRAY OF BYTE");
}

#pragma clang diagnostic pop