#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Type_Declaration_Runner = Parser_Value_Runner<lloberon::sema::Type_Declaration, &lloberon::Parser::parse_type_declaration>;

TEST(Type_Declaration_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner("", type_declaration, true);
}

TEST(Type_Declaration_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner("a* = INTEGER", type_declaration);
}

TEST(Type_Declaration_Tests, incomplete) {
    lloberon::Scope scope;
    lloberon::sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner("a =", type_declaration, true);

    type_declaration.clear();
    Type_Declaration_Runner("a", type_declaration, true);
}

#pragma clang diagnostic pop