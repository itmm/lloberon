#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Heading_Runner = Parser_Value_Runner<
    lloberon::sema::Procedure_Heading, &lloberon::Parser::parse_procedure_heading
>;

TEST(Procedure_Heading_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Procedure_Heading procedure_heading { scope };
    Procedure_Heading_Runner("", procedure_heading, true);
}

TEST(Procedure_Heading_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Procedure_Heading procedure_heading { scope };
    Procedure_Heading_Runner("PROCEDURE f(x: INTEGER): INTEGER", procedure_heading);
}

TEST(Procedure_Heading_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Procedure_Heading procedure_heading { scope };
    Procedure_Heading_Runner("PROCEDURE f", procedure_heading, true);

    procedure_heading.clear();
    Procedure_Heading_Runner("PROCEDURE (): INTEGER", procedure_heading, true, true);
}

#pragma clang diagnostic pop