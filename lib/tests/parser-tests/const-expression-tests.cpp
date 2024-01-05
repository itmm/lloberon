#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Const_Expression_Runner = Parser_String_Runner<&Parser::parse_const_expression>;

TEST(Const_Expression_Tests, empty) {
    Const_Expression_Runner("", true);
}

TEST(Const_Expression_Tests, literals) {
    Const_Expression_Runner("234");
    Const_Expression_Runner("-234");
    Const_Expression_Runner("2.34");
    Const_Expression_Runner("NIL");
    Const_Expression_Runner("TRUE");
    Const_Expression_Runner("FALSE");
}

TEST(Const_Expression_Tests, expressions) {
    Const_Expression_Runner("3 + 4 * 2");
    Const_Expression_Runner("2 < 4 # FALSE");
}

#pragma clang diagnostic pop