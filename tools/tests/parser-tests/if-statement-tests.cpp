#include "parser-tests.h"

using If_Statement_Runner = Parser_Value_Runner<
    sema::If_Statement, &Parser::parse_if_statement
>;

TEST(If_Statement_Tests, empty) {
    Scope scope;
    sema::If_Statement if_statement { scope };
    If_Statement_Runner test1 { "", if_statement, true };
}

TEST(If_Statement_Tests, simple) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "b", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "cond", nullptr
    ));
    sema::If_Statement if_statement { scope };
    If_Statement_Runner test1 { "IF cond THEN a := 1; b := TRUE END", if_statement };
}

TEST(If_Statement_Tests, with_else) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "b", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "cond", nullptr
    ));
    sema::If_Statement if_statement { scope };
    If_Statement_Runner test1 { "IF cond THEN a := 1 ELSE a := 2; b := TRUE END", if_statement };
}

TEST(If_Statement_Tests, with_elsif) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::If_Statement if_statement { scope };
    If_Statement_Runner test1{
            "IF a < 3 THEN a := -1 ELSIF a > 3 THEN a := 1 ELSE a := 0 END", if_statement
    };
}