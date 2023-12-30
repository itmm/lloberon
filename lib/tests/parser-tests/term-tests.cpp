#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Term_Runner = Parser_String_Runner<&lloberon::Parser::parse_term>;

TEST(Term_Tests, empty) {
    Term_Runner("", true);
}

TEST(Term_Tests, single) {
    Term_Runner("3");
}

TEST(Term_Tests, simple) {
    Term_Runner("a * b");
    Term_Runner("a / b");
    Term_Runner("a DIV b");
    Term_Runner("a MOD b");
    Term_Runner("a & b");
}

TEST(Term_Tests, multiple) {
    Term_Runner("a * b * c");
    Term_Runner("a / 2 DIV b");
}

TEST(Term_Runner, incomplete) {
    Term_Runner("a / 2 DIV", true);
    Term_Runner("a /", true);
}

#pragma clang diagnostic pop