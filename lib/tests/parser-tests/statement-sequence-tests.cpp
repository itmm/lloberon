#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Statement_Sequence_Runner = Parser_Value_Runner<
    lloberon::sema::Statement_Sequence, &Parser::parse_statement_sequence
>;

TEST(Statement_Sequence_Tests, empty) {
    Scope scope;
    lloberon::sema::Statement_Sequence statement_sequence { scope };
    Statement_Sequence_Runner("", statement_sequence);
}

TEST(Statement_Sequence_Tests, single) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    lloberon::sema::Statement_Sequence statement_sequence { scope };
    Statement_Sequence_Runner("a := 3", statement_sequence);
}

TEST(Statement_Sequence_Tests, multiple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
            nullptr, {}, "b", nullptr
    });
    lloberon::sema::Statement_Sequence statement_sequence { scope };
    Statement_Sequence_Runner("a := 3;", statement_sequence);

    statement_sequence.clear();
    Statement_Sequence_Runner("a := 3; b := 4", statement_sequence);

    statement_sequence.clear();
    Statement_Sequence_Runner("a := 3; b := 4;", statement_sequence);
}

#pragma clang diagnostic pop