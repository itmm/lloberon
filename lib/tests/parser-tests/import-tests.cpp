#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Import_Runner = Parser_String_Runner<&lloberon::Parser::parse_import>;

TEST(Import_Tests, empty) {
    Import_Runner("", true);
}

TEST(Import_Tests, simple) {
    Import_Runner("a");
    Import_Runner("a := b");
}

TEST(Import_Tests, missing) {
    Import_Runner("a b", false, true);
    Import_Runner("a :=", true);
}

#pragma clang diagnostic pop