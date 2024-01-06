#include "parser-tests.h"

using Label_Range_Runner = Parser_String_Runner<&Parser::parse_label_range>;

TEST(Label_Range_Tests, empty) {
    Label_Range_Runner test1 { "", true };
}

TEST(Label_Range_Tests, simple) {
    Label_Range_Runner test1 { "3" };
    Label_Range_Runner test2 { "3..5" };
}

TEST(Label_Range_Tests, incomplete) {
    Label_Range_Runner test1 { "3..", true };
}