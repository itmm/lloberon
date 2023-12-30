#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Type_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_type_declaration>;

TEST(Type_Declaration_Tests, empty) {
    Type_Declaration_Runner("", true);
}

TEST(Type_Declaration_Tests, simple) {
    Type_Declaration_Runner("a* = INTEGER");
}

TEST(Type_Declaration_Tests, incomplete) {
    Type_Declaration_Runner("a =", true);
    Type_Declaration_Runner("a", true);
}

#pragma clang diagnostic pop