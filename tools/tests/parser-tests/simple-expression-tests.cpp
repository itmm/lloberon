#include "parser-tests.h"
#include "decl/variable.h"
#include "expr/bool.h"
#include "expr/integer.h"

using Simple_Expression_Runner = Parser_Value_Runner<sema::Expression, &Parser::parse_simple_expression>;

TEST(Simple_Expression_Tests, empty) {
    Scope scope;
    sema::Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "", simple_expression, true };
}

void expect_int(const sema::Expression& expression, int expected) {
    auto value { std::dynamic_pointer_cast<expr::Integer>(expression.expression) };
    EXPECT_EQ(value->value, expected);
}

void expect_int(const char* source, int expected) {
    Scope scope;
    sema::Expression expression { scope };
    Simple_Expression_Runner runner { source, expression };
    expect_int(expression, expected);
}

TEST(Simple_Expression_Tests, single) {
    expect_int("345", 345);
}

TEST(Simple_Expression_Tests, simple) {
    expect_int("3 + 4", 7);
    expect_int("3 - 4", -1);

    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("b", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Expression simple_expression { scope };
    Simple_Expression_Runner test3 { "a OR b", simple_expression };
}

void expect_bool(const sema::Expression& expression, bool expected) {
    auto value { std::dynamic_pointer_cast<expr::Bool>(expression.expression) };
    if (expected) {
        EXPECT_TRUE(value->value);
    } else {
        EXPECT_FALSE(value->value);
    }
}

void expect_bool(const char* source, bool expected) {
    Scope scope;
    sema::Expression expression { scope };
    Simple_Expression_Runner runner { source, expression };
    expect_bool(expression, expected);
}

void expect_true(const char* source) { expect_bool(source, true); }

void expect_false(const char* source) { expect_bool(source, false); }

TEST(Simple_Expression_Tests, constant_or) {
    expect_false("FALSE OR FALSE");
    expect_true("FALSE OR TRUE");
    expect_true("TRUE OR TRUE");
    expect_true("TRUE OR TRUE");
}

TEST(Simple_Expression_Tests, factor) {
    Scope scope;
    sema::Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "3 * 4", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "3 / 2 + 4 * 3", simple_expression };
}

TEST(Simple_Expression_Tests, unaries) {
    Scope scope;
    sema::Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "+3", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "-3 + 4", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test3 { "+-3", simple_expression, true, true };
}

TEST(Simple_Expression_Tests, incomplete) {
    Scope scope;
    sema::Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "3 +", simple_expression, true };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "+", simple_expression, true };
}