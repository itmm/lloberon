#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Case_Runner = Parser_String_Runner<&lloberon::Parser::parse_case>;

TEST(Case_Tests, empty) {
    Case_Runner("", true);
}

TEST(Case_Tests, simple) {
    Case_Runner("3..4:");
    Case_Runner("3..4: a := 3");
}

TEST(Case_Tests, wrong) {
    Case_Runner("3 a := 3", true, true);
    Case_Runner("3", true);
}

#pragma clang diagnostic pop