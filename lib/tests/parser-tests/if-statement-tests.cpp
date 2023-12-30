#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using If_Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_if_statement>;

TEST(If_Statement_Tests, empty) {
    If_Statement_Runner("", true);
}

TEST(If_Statement_Tests, simple) {
    If_Statement_Runner("IF cond THEN a := 1; b := TRUE END");
}

TEST(If_Statement_Tests, with_else) {
    If_Statement_Runner("IF cond THEN a := 1 ELSE a := 2; b := TRUE END");
}

TEST(If_Statement_Tests, with_elsif) {
    If_Statement_Runner("IF a < 3 THEN a := -1 ELSIF a > 3 THEN a := 1 ELSE a := 0 END");
}

#pragma clang diagnostic pop