#include "parser-tests.h"

using Var_Declaration_Runner = Parser_Value_Runner<sema::Var_Declaration, &Parser::parse_variable_declaration>;

TEST(Var_Declaration_Tests, empty) {
    Scope scope;
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner test1 { "", var_declaration, true };
}

TEST(Var_Declaration_Tests, simple) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner test1 { "a*: INTEGER", var_declaration };
}

TEST(Var_Declaration_Tests, incomplete) {
    Scope scope;
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner test1 { "a:", var_declaration, true };

    var_declaration.clear();
    Var_Declaration_Runner test2 { "a", var_declaration, true };
}

TEST(Var_Declaration_Tests, invalid) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner test1 { "a INTEGER", var_declaration, true, true };

    var_declaration.clear();
    Var_Declaration_Runner test2 { "a;", var_declaration, true, true };
}