#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Base_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_base_type>;

TEST(Base_Type_Tests, empty) {
    Base_Type_Runner("", true);
}

TEST(Base_Type_Tests, simple) {
    Base_Type_Runner("BYTE");
}

TEST(Base_Type_Tests, qualified) {
    Base_Type_Runner("SYSTEM.Byte");
}

#pragma clang diagnostic pop