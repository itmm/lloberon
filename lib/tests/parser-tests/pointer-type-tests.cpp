#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Pointer_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_pointer_type>;

TEST(Pointer_Type_Tests, empty) {
    Pointer_Type_Runner("", true);
}

TEST(Pointer_Type_Tests, simple) {
    Pointer_Type_Runner("POINTER TO Record");
}

TEST(Pointer_Type_Tests, incomplete) {
    Pointer_Type_Runner("POINTER TO", true);
    Pointer_Type_Runner("POINTER Record", true, true);
}

#pragma clang diagnostic pop