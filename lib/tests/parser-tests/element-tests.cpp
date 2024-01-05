#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Element_Runner = Parser_String_Runner<&Parser::parse_element>;

TEST(Element_Tests, empty) {
    Element_Runner("", true);
}

TEST(Element_Tests, simple) {
    Element_Runner("3");
}

TEST(Element_Tests, range) {
    Element_Runner("3..6");
}

TEST(Element_Tests, incomplete) {
    Element_Runner("3..", true);
}

#pragma clang diagnostic pop