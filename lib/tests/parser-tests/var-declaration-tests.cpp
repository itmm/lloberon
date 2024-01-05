#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Var_Declaration_Runner = Parser_Value_Runner<sema::Var_Declaration, &Parser::parse_variable_declaration>;

TEST(Var_Declaration_Tests, empty) {
    Scope scope;
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("", var_declaration, true);
}

TEST(Var_Declaration_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("a*: INTEGER", var_declaration);
}

TEST(Var_Declaration_Tests, incomplete) {
    Scope scope;
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("a:", var_declaration, true);

    var_declaration.clear();
    Var_Declaration_Runner("a", var_declaration, true);
}

TEST(Var_Declaration_Tests, invalid) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("a INTEGER", var_declaration, true, true);

    var_declaration.clear();
    Var_Declaration_Runner("a;", var_declaration, true, true);
}

#pragma clang diagnostic pop