#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Set_Runner = Parser_String_Runner<&lloberon::Parser::parse_set>;

TEST(Set_Tests, empty) {
    Set_Runner("", true);
    Set_Runner("{}");
}

TEST(Set_Tests, simple) {
    Set_Runner("{1}");
    Set_Runner("{1, 2, 3}");
}

TEST(Set_Tests, ranges) {
    Set_Runner("{1..2}");
    Set_Runner("{1..2, 4..6}");
}

TEST(Set_Tests, incomplete) {
    Set_Runner("{1..3", true);
    Set_Runner("{1..}", true);
    Set_Runner("{1,}", true);
    Set_Runner("{1,,", true);
}

#pragma clang diagnostic pop