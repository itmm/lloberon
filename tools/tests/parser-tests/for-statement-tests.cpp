#include "parser-tests.h"
#include "decl/variable.h"

using For_Statement_Runner = Parser_Value_Runner<
    sema::For_Statement, &Parser::parse_for_statement
>;

TEST(For_Statement_Tests, empty) {
    Scope scope;
    sema::For_Statement for_statement { scope };
    For_Statement_Runner test1 { "", for_statement, true };
}

TEST(For_Statement_Tests, simple) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("x", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::For_Statement for_statement { scope };
    For_Statement_Runner test1 { "FOR a := 1 TO 3 DO x := x + a END", for_statement };
}

TEST(For_Statement_Tests, with_step) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("x", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::For_Statement for_statement { scope };
    For_Statement_Runner test1 { "FOR a := 1 TO 10 BY 2 DO x := x + a END", for_statement };
}

TEST(For_Statement_Tests, with_stepdown) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("x", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::For_Statement for_statement { scope };
    For_Statement_Runner test1 { "FOR a := 10 TO 0 BY -2 DO x := x + a END", for_statement };
}

TEST(For_Statement_Tests, wrong) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::For_Statement for_statement { scope };
    For_Statement_Runner test1 { "FOR", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test2 { "FOR a", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test3 { "FOR :=", for_statement, true, true };

    for_statement.clear();
    For_Statement_Runner test4 { "FOR a :=", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test5 { "FOR a 1", for_statement, true, true };

    for_statement.clear();
    For_Statement_Runner test6 { "FOR a := 1", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test7 { "FOR a := 1 TO", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test8 { "FOR a := 1 TO 10", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test9 { "FOR a := 1 10", for_statement, true, true };

    for_statement.clear();
    For_Statement_Runner test10 { "FOR a := 1 TO 10 DO", for_statement, true };

    for_statement.clear();
    For_Statement_Runner test11 { "FOR a := 1 TO 10 END", for_statement, true, true };

    for_statement.clear();
    For_Statement_Runner test12 { "FOR a := 1 TO 10 BY DO", for_statement, true, true };
}