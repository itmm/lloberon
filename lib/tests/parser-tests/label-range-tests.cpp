#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Label_Range_Runner = Parser_String_Runner<&Parser::parse_label_range>;

TEST(Label_Range_Tests, empty) {
    Label_Range_Runner("", true);
}

TEST(Label_Range_Tests, simple) {
    Label_Range_Runner("3");
    Label_Range_Runner("3..5");
}

TEST(Label_Range_Tests, incomplete) {
    Label_Range_Runner("3..", true);
}

#pragma clang diagnostic pop