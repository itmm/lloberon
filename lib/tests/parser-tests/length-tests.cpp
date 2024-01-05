#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Length_Runner = Parser_String_Runner<&Parser::parse_length>;

TEST(Length_Tests, empty) {
    Length_Runner("", true);
}

TEST(Length_Tests, simple) {
    Length_Runner("3");
}

#pragma clang diagnostic pop