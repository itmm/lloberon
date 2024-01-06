#include "parser-tests.h"

using Const_Expression_Runner = Parser_String_Runner<&Parser::parse_const_expression>;

TEST(Const_Expression_Tests, empty) {
    Const_Expression_Runner("", true);
}

TEST(Const_Expression_Tests, literals) {
    Const_Expression_Runner test1 { "234" };
    Const_Expression_Runner test2 { "-234" };
    Const_Expression_Runner test3 { "2.34" };
    Const_Expression_Runner test4 { "NIL" };
    Const_Expression_Runner test5 { "TRUE" };
    Const_Expression_Runner test6 { "FALSE" };
}

TEST(Const_Expression_Tests, expressions) {
    Const_Expression_Runner test1 { "3 + 4 * 2" };
    Const_Expression_Runner test2 { "2 < 4 # FALSE" };
}