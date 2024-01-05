#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Type_Runner = Parser_Value_Runner<lloberon::sema::Procedure_Type, &Parser::parse_procedure_type>;

TEST(Procedure_Type_Tests, empty) {
    Scope scope;
    lloberon::sema::Procedure_Type procedure_type { scope };
    Procedure_Type_Runner("", procedure_type, true);
}

TEST(Procedure_Type_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Procedure_Type procedure_type { scope };
    Procedure_Type_Runner("PROCEDURE (a: INTEGER): INTEGER", procedure_type);
}

#pragma clang diagnostic pop