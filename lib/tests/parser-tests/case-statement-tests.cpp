#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Case_Statement_Runner = Parser_Value_Runner<
    lloberon::sema::Case_Statement, &lloberon::Parser::parse_case_statement
>;

TEST(Case_Statetment_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("", case_statement, true);
}

TEST(Case_Statement_Tests, single) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "x", nullptr
    });
    lloberon::sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("", case_statement, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a OF 3: x := 1 END", case_statement);
}

TEST(Case_Statement_Tests, multiple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "x", nullptr
    });
    lloberon::sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("CASE a OF 3: x := 1 | 2, 4: x := 2 END", case_statement);
}

TEST(Case_Statement_Tests, wrong) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    lloberon::sema::Case_Statement case_statement { scope };
    Case_Statement_Runner("CASE OF", case_statement, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a 3:", case_statement, true, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a OF END", case_statement, true, true);

    case_statement.clear();
    Case_Statement_Runner("CASE a OF 3: |", case_statement, true);
}

#pragma clang diagnostic pop