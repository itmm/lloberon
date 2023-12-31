#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using While_Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_while_statement>;

TEST(While_Statement_Tests, empty) {
    While_Statement_Runner("", true);
}

TEST(While_Statement_Tests, simple) {
    While_Statement_Runner("WHILE a < 3 DO INC(a) END");
}

TEST(While_Statement_Tests, with_elsif) {
    While_Statement_Runner(
        "WHILE a < 3 DO INC(a) ELSIF b < 3 DO INC(b) ELSIF c < 3 DO INC(c) END"
    );
}

TEST(While_Statement_Runner, wrong) {
    While_Statement_Runner("WHILE DO", true);
    While_Statement_Runner("WHILE a < 3 DO INC(a)", true);
    While_Statement_Runner("WHILE a ELSIF", true, true);
    While_Statement_Runner("WHILE a < 3 DO ELSIF END", true);
}

#pragma clang diagnostic pop