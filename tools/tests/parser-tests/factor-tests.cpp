#include "parser-tests.h"
#include "decl/declaration.h"
#include "decl/variable.h"
#include "expr/int-literal.h"

using Factor_Runner = Parser_Value_Runner<sema::Expression, &Parser::parse_factor>;

TEST(Factor_Tests, empty) {
    Scope scope;
    sema::Expression factor { scope };
    Factor_Runner("", factor, true);
}

TEST(Factor_Tests, literals) {
    Scope scope;
    sema::Expression factor { scope };
    Factor_Runner test1 { "3", factor };
    auto int_factor { std::dynamic_pointer_cast<expr::Int_Literal>(factor.expression) };
    EXPECT_NE(int_factor, nullptr);
    EXPECT_EQ(int_factor->value, 3);

    factor.clear();
    Factor_Runner test2 { "3.241", factor };
    factor.clear();
    Factor_Runner test3 { "\"abc\"", factor };
    factor.clear();
    Factor_Runner test4 { "NIL", factor };
    factor.clear();
    Factor_Runner test5 { "TRUE", factor };
    factor.clear();
    Factor_Runner test6 { "FALSE", factor };
}

TEST(Factor_Tests, set) {
    Scope scope;
    sema::Expression factor { scope };
    Factor_Runner test1 { "{3..5}", factor };
}

TEST(Factor_Tests, grouped) {
    Scope scope;
    sema::Expression factor { scope };
    Factor_Runner test1 { "(3 + 4)", factor };
}

TEST(Factor_Tests, ident) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Expression factor { scope };
    Factor_Runner test1 { "a", factor };
    factor.clear();
    Factor_Runner test2 { "a(3, TRUE)", factor };
    factor.clear();
    Factor_Runner test3 { "a[3](TRUE)", factor };
}

TEST(Factor_Tests, incomplete) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Expression factor { scope };
    Factor_Runner test1 { "a(3,TRUE", factor, true };
    factor.clear();
    Factor_Runner test2 { "a(3,", factor, true };
    factor.clear();
    Factor_Runner test3 { "a(3", factor, true };
    factor.clear();
    Factor_Runner test4 { "a(", factor, true };
}