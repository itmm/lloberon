#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Statement_Sequence_Runner = Parser_String_Runner<&lloberon::Parser::parse_statement_sequence>;

TEST(Statement_Sequence_Tests, empty) {
    Statement_Sequence_Runner("");
}

TEST(Statement_Sequence_Runner, single) {
    Statement_Sequence_Runner("a := 3");
}

TEST(Statement_Sequence_Runner, multiple) {
    Statement_Sequence_Runner("a := 3;");
    Statement_Sequence_Runner("a := 3; b := 4");
    Statement_Sequence_Runner("a := 3; b := 4;");
}

#pragma clang diagnostic pop