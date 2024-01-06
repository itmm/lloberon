#include "parser-tests.h"

using Statement_Sequence_Runner = Parser_Value_Runner<
    sema::Statement_Sequence, &Parser::parse_statement_sequence
>;

TEST(Statement_Sequence_Tests, empty) {
    Scope scope;
    sema::Statement_Sequence statement_sequence { scope };
    Statement_Sequence_Runner test1 { "", statement_sequence };
}

TEST(Statement_Sequence_Tests, single) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::Statement_Sequence statement_sequence { scope };
    Statement_Sequence_Runner test1 { "a := 3", statement_sequence };
}

TEST(Statement_Sequence_Tests, multiple) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    scope.insert(std::make_shared<decl::Variable>(
            nullptr, llvm::SMLoc {}, "b", nullptr
    ));
    sema::Statement_Sequence statement_sequence { scope };
    Statement_Sequence_Runner test1 { "a := 3;", statement_sequence };

    statement_sequence.clear();
    Statement_Sequence_Runner test2 { "a := 3; b := 4", statement_sequence };

    statement_sequence.clear();
    Statement_Sequence_Runner test3 { "a := 3; b := 4;", statement_sequence };
}