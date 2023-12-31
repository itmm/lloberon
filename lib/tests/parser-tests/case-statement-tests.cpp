#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Case_Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_case_statement>;

TEST(Case_Statetment_Tests, empty) {
    Case_Statement_Runner("", true);
}

TEST(Case_Statement_Tests, single) {
    Case_Statement_Runner("CASE a OF 3: x := 1 END");
}

TEST(Case_Statement_Tests, multiple) {
    Case_Statement_Runner("CASE a OF 3: x := 1 | 2, 4: x := 2 END");
}

TEST(Case_Statement_Tests, wrong) {
    Case_Statement_Runner("CASE OF", true);
    Case_Statement_Runner("CASE a 3:", true, true);
    Case_Statement_Runner("CASE a OF END", true, true);
    Case_Statement_Runner("CASE a OF 3: |", true);
}

#pragma clang diagnostic pop