#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using For_Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_for_statement>;

TEST(For_Statement_Tests, empty) {
    For_Statement_Runner("", true);
}

TEST(For_Statement_Tests, simple) {
    For_Statement_Runner("FOR a := 1 TO 3 DO x := x + a END");
}

TEST(For_Statement_Tests, with_step) {
    For_Statement_Runner("FOR a := 1 TO 10 BY 2 DO x := x + a END");
}

TEST(For_Statement_Tests, with_stepdown) {
    For_Statement_Runner("FOR a := 10 TO 0 BY -2 DO x := x + a END");
}

TEST(For_Statement_Tests, wrong) {
    For_Statement_Runner("FOR", true);
    For_Statement_Runner("FOR a", true);
    For_Statement_Runner("FOR :=", true, true);
    For_Statement_Runner("FOR a :=", true);
    For_Statement_Runner("FOR a 1", true, true);
    For_Statement_Runner("FOR a := 1", true);
    For_Statement_Runner("FOR a := 1 TO", true);
    For_Statement_Runner("FOR a := 1 TO 10", true);
    For_Statement_Runner("FOR a := 1 10", true, true);
    For_Statement_Runner("FOR a := 1 TO 10 DO", true);
    For_Statement_Runner("FOR a := 1 TO 10 END", true, true);
    For_Statement_Runner("FOR a := 1 TO 10 BY DO", true);
}

#pragma clang diagnostic pop