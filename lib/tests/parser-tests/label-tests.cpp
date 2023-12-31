#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Label_Runner = Parser_String_Runner<&lloberon::Parser::parse_label>;

TEST(Label_Tests, empty) {
    Label_Runner("", true);
}

TEST(Label_Tests, simple) {
    Label_Runner("3");
    Label_Runner("\"abc\"");
}

TEST(Label_Tests, qual_ident) {
    Label_Runner("INTEGER");
    Label_Runner("SYSTEM.Byte");
}

TEST(Label_Tests, wrong) {
    Label_Runner("SYSTEM.", true);
    Label_Runner("NIL", true, true);
}

#pragma clang diagnostic pop