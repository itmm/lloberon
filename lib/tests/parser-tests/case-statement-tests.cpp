#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Case_Statement_Runner = Parser_Value_Runner<
    sema::Case_Statement, &Parser::parse_case_statement
>;

TEST(Case_Statetment_Tests, empty) {
    Scope scope;
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("", case_statement, true);
}

TEST(Case_Statement_Tests, single) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
        nullptr, {}, "x", nullptr
    });
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("", case_statement, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a OF 3: x := 1 END", case_statement);
}

TEST(Case_Statement_Tests, multiple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
            nullptr, {}, "x", nullptr
    });
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("CASE a OF 3: x := 1 | 2, 4: x := 2 END", case_statement);
}

TEST(Case_Statement_Tests, wrong) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("CASE OF", case_statement, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a 3:", case_statement, true, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a OF END", case_statement, true, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a OF 3: |", case_statement, true);
}

#pragma clang diagnostic pop