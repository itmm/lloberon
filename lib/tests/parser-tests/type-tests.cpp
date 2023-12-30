#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_type>;

TEST(Type_Tests, empty) {
    Type_Runner("", true);
}

TEST(Type_Tests, simple) {
    Type_Runner("INTEGER");
    Type_Runner("ARRAY 10 OF INTEGER");
    Type_Runner("RECORD x, y: INTEGER END");
    Type_Runner("POINTER TO Entry");
    Type_Runner("PROCEDURE (a: INTEGER): BYTE");
}

TEST(Type_Tests, invalid) {
    Type_Runner(":", true, true);
}

#pragma clang diagnostic pop