#include "parser-tests.h"
#include "decl/variable.h"

using Simple_Expression_Runner = Parser_Value_Runner<sema::Simple_Expression, &Parser::parse_simple_expression>;

TEST(Simple_Expression_Tests, empty) {
    Scope scope;
    sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "", simple_expression, true };
}

TEST(Simple_Expression_Tests, single) {
    Scope scope;
    sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "3", simple_expression };
}

TEST(Simple_Expression_Tests, simple) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "b", nullptr
    ));
    sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "3 + 4", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "3 - 4", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test3 { "a OR b", simple_expression };
}

TEST(Simple_Expression_Tests, factor) {
    Scope scope;
    sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "3 * 4", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "3 / 2 + 4 * 3", simple_expression };
}

TEST(Simple_Expression_Tests, unaries) {
    Scope scope;
    sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "+3", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "-3 + 4", simple_expression };

    simple_expression.clear();
    Simple_Expression_Runner test3 { "+-3", simple_expression, true, true };
}

TEST(Simple_Expression_Tests, incomplete) {
    Scope scope;
    sema::Simple_Expression simple_expression { scope };
    Simple_Expression_Runner test1 { "3 +", simple_expression, true };

    simple_expression.clear();
    Simple_Expression_Runner test2 { "+", simple_expression, true };
}