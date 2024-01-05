#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Body_Runner = Parser_Value_Runner<
    lloberon::sema::Procedure_Body, &lloberon::Parser::parse_procedure_body
>;

TEST(Procedure_Body_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner("", procedure_body, true);
}

TEST(Procedure_Body_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    lloberon::sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner("END", procedure_body);

    procedure_body.clear();
    Procedure_Body_Runner("RETURN 42 END", procedure_body);

    procedure_body.clear();
    Procedure_Body_Runner("BEGIN RETURN 42 END", procedure_body);

    procedure_body.clear();
    Procedure_Body_Runner("BEGIN a := 42; RETURN a END", procedure_body);
}

TEST(Procedure_Body_Tests, with_declaration) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner("VAR a: INTEGER; BEGIN a := 42 END", procedure_body);

    procedure_body.clear();
    Procedure_Body_Runner("CONST a = 42; RETURN a END", procedure_body);
}

TEST(Procedure_Body_Tests, invalid) {
    lloberon::Scope scope;
    lloberon::sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner("RETURN END", procedure_body, true);
}

#pragma clang diagnostic pop