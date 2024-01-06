#include "parser-tests.h"

using Statement_Runner = Parser_Value_Runner<
    sema::Statement, &Parser::parse_statement
>;

TEST(Statement_Tests, empty) {
    Scope scope;
    sema::Statement statement { scope };
    Statement_Runner("", statement);
}

TEST(Statement_Tests, single) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "b", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "i", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "cond", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "f", nullptr
    ));
    sema::Statement statement { scope };
    Statement_Runner test1 { "a := 3", statement };

    statement.clear();
    Statement_Runner test2 { "f(2, 3)", statement };

    statement.clear();
    Statement_Runner test3 { "IF b THEN a := 3 END", statement };

    statement.clear();
    Statement_Runner test4 { "CASE cond OF 3: a := 3 END", statement };

    statement.clear();
    Statement_Runner test5 { "WHILE cond DO END", statement };

    statement.clear();
    Statement_Runner test6 { "REPEAT UNTIL cond", statement };

    statement.clear();
    Statement_Runner test7 { "FOR i := 1 TO 10 DO END", statement };
}

TEST(Statement_Tests, invalid) {
    Scope scope;
    sema::Statement statement { scope };
    Statement_Runner test1 { "3", statement, false, true };
}