#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Declaration_Runner = Parser_Value_Runner<
    lloberon::sema::Procedure_Declaration, &lloberon::Parser::parse_procedure_declaration
>;

TEST(Procedure_Declaration_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Procedure_Declaration procedure_declaration { scope };
    Procedure_Declaration_Runner("", procedure_declaration, true);
}

TEST(Procedure_Declaration_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "x", nullptr
    });
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Procedure_Declaration procedure_declaration { scope };
    Procedure_Declaration_Runner(
        "PROCEDURE Add1(x: INTEGER): INTEGER; RETURN x + 1 END Add1", procedure_declaration
    );
}

TEST(Procedure_Declaration_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Procedure_Declaration procedure_declaration { scope };
    Procedure_Declaration_Runner("PROCEDURE RETURN", procedure_declaration, true, true);

    procedure_declaration.clear();
    Procedure_Declaration_Runner("PROCEDURE Answer(): INTEGER; RETURN", procedure_declaration, true);
}

#pragma clang diagnostic pop