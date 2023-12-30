#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Expression_Runner = Parser_String_Runner<&lloberon::Parser::parse_expression>;

TEST(Expression_Tests, empty) {
    Expression_Runner("", true);
}

TEST(Expression_Tests, single) {
    Expression_Runner("3 = 4");
    Expression_Runner("3 # 4");
    Expression_Runner("3 < 4");
    Expression_Runner("3 <= 4");
    Expression_Runner("3 > 4");
    Expression_Runner("3 >= 4");
    Expression_Runner("3 IN a");
    Expression_Runner("a IS b");
}

TEST(Expression_Tests, multiple) {
    Expression_Runner("3 < 4 = TRUE");
}

TEST(Expression_Tests, invalid) {
    Expression_Runner("}", true);
}

#pragma clang diagnostic pop