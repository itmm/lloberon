#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Var_Declaration_Runner = Parser_Value_Runner<lloberon::sema::Var_Declaration, &lloberon::Parser::parse_variable_declaration>;

TEST(Var_Declaration_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("", var_declaration, true);
}

TEST(Var_Declaration_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("a*: INTEGER", var_declaration);
}

TEST(Var_Declaration_Tests, incomplete) {
    lloberon::Scope scope;
    lloberon::sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("a:", var_declaration, true);

    var_declaration.clear();
    Var_Declaration_Runner("a", var_declaration, true);
}

TEST(Var_Declaration_Tests, invalid) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Var_Declaration var_declaration { scope };
    Var_Declaration_Runner("a INTEGER", var_declaration, true, true);

    var_declaration.clear();
    Var_Declaration_Runner("a;", var_declaration, true, true);
}

#pragma clang diagnostic pop