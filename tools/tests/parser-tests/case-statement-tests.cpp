#include "parser-tests.h"
#include "decl/variable.h"

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
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("x", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner test1 { "", case_statement, true };

    case_statement.clear();
    Case_Statement_Runner test2 { "CASE a OF 3: x := 1 END", case_statement };
}

TEST(Case_Statement_Tests, multiple) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("x", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner test1 {
        "CASE a OF 3: x := 1 | 2, 4: x := 2 END", case_statement
    };
}

TEST(Case_Statement_Tests, wrong) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Case_Statement case_statement { scope };
    Case_Statement_Runner test1 { "CASE OF", case_statement, true, true };

    case_statement.clear();
    Case_Statement_Runner test2 { "CASE a 3:", case_statement, true, true };

    case_statement.clear();
    Case_Statement_Runner test3 { "CASE a OF END", case_statement, true, true };

    case_statement.clear();
    Case_Statement_Runner test4 { "CASE a OF 3: |", case_statement, true };
}