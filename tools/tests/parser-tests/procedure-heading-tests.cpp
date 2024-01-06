#include "parser-tests.h"
#include "decl/base-type.h"

using Procedure_Heading_Runner = Parser_Value_Runner<
    sema::Procedure_Heading, &Parser::parse_procedure_heading
>;

TEST(Procedure_Heading_Tests, empty) {
    Scope scope;
    sema::Procedure_Heading procedure_heading { scope };
    Procedure_Heading_Runner test1 { "", procedure_heading, true };
}

TEST(Procedure_Heading_Tests, simple) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Procedure_Heading procedure_heading { scope };
    Procedure_Heading_Runner test1 { "PROCEDURE f(x: INTEGER): INTEGER", procedure_heading };
}

TEST(Procedure_Heading_Tests, incomplete) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Procedure_Heading procedure_heading { scope };
    Procedure_Heading_Runner test1 { "PROCEDURE f", procedure_heading, true };

    procedure_heading.clear();
    Procedure_Heading_Runner test2 { "PROCEDURE (): INTEGER", procedure_heading, true, true };
}