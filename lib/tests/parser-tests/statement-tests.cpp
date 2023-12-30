#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_statement>;

TEST(Statement_Tests, empty) {
    Statement_Runner("");
}

TEST(Statement_Tests, single) {
    Statement_Runner("a := 3");
    Statement_Runner("f(2, 3)");
    Statement_Runner("IF b THEN a := 3 END");
    Statement_Runner("CASE cond OF 3: a := 3 END");
    Statement_Runner("WHILE cond DO END");
    Statement_Runner("REPEAT UNTIL cond");
    Statement_Runner("FOR i := 1 TO 10 DO END");
}

TEST(Statement_Tests, invalid) {
    Statement_Runner("3", false, true);
}

#pragma clang diagnostic pop