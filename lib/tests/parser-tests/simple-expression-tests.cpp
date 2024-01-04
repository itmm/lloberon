#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Simple_Expression_Runner = Parser_String_Runner<&lloberon::Parser::parse_simple_expression>;

TEST(Simple_Expression_Tests, empty) {
    Simple_Expression_Runner("", true);
}

TEST(Simple_Expression_Tests, single) {
    Simple_Expression_Runner("3");
}

TEST(Simple_Expression_Tests, simple) {
    Simple_Expression_Runner("3 + 4");
    Simple_Expression_Runner("3 - 4");
    Simple_Expression_Runner("a OR b");
}

TEST(Simple_Expression_Tests, factor) {
    Simple_Expression_Runner("3 * 4");
    Simple_Expression_Runner("3 / 2 + 4 * 3");
}

TEST(Simple_Expression_Tests, unaries) {
    Simple_Expression_Runner("+3");
    Simple_Expression_Runner("-3 + 4");
    Simple_Expression_Runner("+-3", true, true);
}

TEST(Simple_Expression_Tests, incomplete) {
    Simple_Expression_Runner("3 +", true);
    Simple_Expression_Runner("+", true);
}

#pragma clang diagnostic pop