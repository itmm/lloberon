#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Factor_Runner = Parser_String_Runner<&lloberon::Parser::parse_factor>;

TEST(Factor_Tests, empty) {
    Factor_Runner("", true);
}

TEST(Factor_Tests, literals) {
    Factor_Runner("3");
    Factor_Runner("3.241");
    Factor_Runner("\"abc\"");
    Factor_Runner("NIL");
    Factor_Runner("TRUE");
    Factor_Runner("FALSE");
}

TEST(Factor_Tests, set) {
    Factor_Runner("{3..5}");
}

TEST(Factor_Tests, grouped) {
    Factor_Runner("(3 + 4)");
}

TEST(Factor_Tests, ident) {
    Factor_Runner("a");
    Factor_Runner("a(3, TRUE)");
    Factor_Runner("a[3](TRUE)");
}

TEST(Factor_Tests, incomplete) {
    Factor_Runner("a(3,TRUE", true);
    Factor_Runner("a(3,", true);
    Factor_Runner("a(3", true);
    Factor_Runner("a(", true);
}

#pragma clang diagnostic pop