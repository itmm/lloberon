#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Assignment_Runner = Parser_Value_Runner<
    lloberon::sema::Assignment_Or_Procedure_Call,
    &lloberon::Parser::parse_assignment_or_procedure_call
>;
using Procedure_Call_Runner = Assignment_Runner;

TEST(Assignment_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Assignment_Or_Procedure_Call assignment { scope };
    Assignment_Runner("", assignment, true);
}

TEST(Assignment_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    lloberon::sema::Assignment_Or_Procedure_Call assignment { scope };
    Assignment_Runner("a := 3", assignment);
}

TEST(Assignment_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    lloberon::sema::Assignment_Or_Procedure_Call assignment { scope };
    Assignment_Runner("a :=", assignment, true);
}

TEST(Procedure_Call_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "f", nullptr
    });
    lloberon::sema::Assignment_Or_Procedure_Call assignment { scope };
    Procedure_Call_Runner("f()", assignment);

    assignment.clear();
    Procedure_Call_Runner("f(a, 3)", assignment);
}

TEST(Procedure_Call_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "f", nullptr
    });
    lloberon::sema::Assignment_Or_Procedure_Call assignment { scope };
    Procedure_Call_Runner("f(a,", assignment, true);

    assignment.clear();
    Procedure_Call_Runner("f(a", assignment, true);

    assignment.clear();
    Procedure_Call_Runner("f(", assignment, true);
}

TEST(Procedure_Call_Tests, cast) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Assignment_Or_Procedure_Call assignment { scope };
    Procedure_Call_Runner("a (INTEGER)", assignment);
}

#pragma clang diagnostic pop