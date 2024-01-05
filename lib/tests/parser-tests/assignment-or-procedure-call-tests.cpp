#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Assignment_Runner = Parser_Value_Runner<
    sema::Assignment_Or_Procedure_Call,
    &Parser::parse_assignment_or_procedure_call
>;
using Procedure_Call_Runner = Assignment_Runner;

TEST(Assignment_Tests, empty) {
    Scope scope;
    sema::Assignment_Or_Procedure_Call assignment { scope };
    Assignment_Runner("", assignment, true);
}

TEST(Assignment_Tests, simple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    sema::Assignment_Or_Procedure_Call assignment { scope };
    Assignment_Runner("a := 3", assignment);
}

TEST(Assignment_Tests, incomplete) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    sema::Assignment_Or_Procedure_Call assignment { scope };
    Assignment_Runner("a :=", assignment, true);
}

TEST(Procedure_Call_Tests, simple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
        nullptr, {}, "f", nullptr
    });
    sema::Assignment_Or_Procedure_Call assignment { scope };
    Procedure_Call_Runner("f()", assignment);

    assignment.clear();
    Procedure_Call_Runner("f(a, 3)", assignment);
}

TEST(Procedure_Call_Tests, incomplete) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
        nullptr, {}, "f", nullptr
    });
    sema::Assignment_Or_Procedure_Call assignment { scope };
    Procedure_Call_Runner("f(a,", assignment, true);

    assignment.clear();
    Procedure_Call_Runner("f(a", assignment, true);

    assignment.clear();
    Procedure_Call_Runner("f(", assignment, true);
}

TEST(Procedure_Call_Tests, cast) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Assignment_Or_Procedure_Call assignment { scope };
    Procedure_Call_Runner("a (INTEGER)", assignment);
}

#pragma clang diagnostic pop