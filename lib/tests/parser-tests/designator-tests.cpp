#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Designator_Runner = Parser_String_Runner<&lloberon::Parser::parse_designator>;

TEST(Designator_Tests, empty) {
    Designator_Runner("", true);
}

TEST(Designator_Tests, simple) {
    Designator_Runner("a");
    Designator_Runner("a.b");
    Designator_Runner("a.b.c");
    Designator_Runner("a.b[2, 3]");
    Designator_Runner("a.b^");
}

TEST(Designator_Tests, combined) {
    Designator_Runner("a.b^[3].c^");
}

TEST(Designator_Tests, incomplete) {
    Designator_Runner("a[3,", true);
    Designator_Runner("a[3", true);
    Designator_Runner("a[3,]", true);
    Designator_Runner("a[]", true);
    Designator_Runner("a.b.", true);
    Designator_Runner("a.b.[", true, true);
    Designator_Runner("a.b.^", true, true);
    Designator_Runner("a.", true);
    Designator_Runner("a.[", true, true);
    Designator_Runner("a.^", true, true);
}

#pragma clang diagnostic pop