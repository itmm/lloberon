#include "parser-tests.h"

using Length_Runner = Parser_Value_Runner<sema::Const_Expression, &Parser::parse_length>;

TEST(Length_Tests, empty) {
    Scope scope;
    sema::Const_Expression expression { scope };
    Length_Runner test1 { "", expression, true };
}

TEST(Length_Tests, simple) {
    Scope scope;
    sema::Const_Expression expression { scope };
    Length_Runner test2 { "3", expression };
}