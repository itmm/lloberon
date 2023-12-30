#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Simple_Expression_Runner = Parser_String_Runner<&lloberon::Parser::parse_simple_expression>;

TEST(Test_Simple_Expressions, empty) {
    Simple_Expression_Runner("", true);
}

TEST(Test_Simple_Expression, single) {
    Simple_Expression_Runner("3");
}

TEST(Test_Simple_Expression, simple) {
    Simple_Expression_Runner("3 + 4");
    Simple_Expression_Runner("3 - 4");
    Simple_Expression_Runner("a OR b");
}

TEST(Test_Simple_Expression, factor) {
    Simple_Expression_Runner("3 * 4");
    Simple_Expression_Runner("3 / 2 + 4 * 3");
}

TEST(Test_Simple_Expression, unaries) {
    Simple_Expression_Runner("+3");
    Simple_Expression_Runner("-3 + 4");
    Simple_Expression_Runner("+-3", true, true);
}

TEST(Test_Simple_Expression, incomplete) {
    Simple_Expression_Runner("3 +", true);
    Simple_Expression_Runner("+", true);
}

#pragma clang diagnostic pop