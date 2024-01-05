#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Type_Declaration_Runner = Parser_Value_Runner<lloberon::sema::Type_Declaration, &Parser::parse_type_declaration>;

TEST(Type_Declaration_Tests, empty) {
    Scope scope;
    lloberon::sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner("", type_declaration, true);
}

TEST(Type_Declaration_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner("a* = INTEGER", type_declaration);
}

TEST(Type_Declaration_Tests, incomplete) {
    Scope scope;
    lloberon::sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner("a =", type_declaration, true);

    type_declaration.clear();
    Type_Declaration_Runner("a", type_declaration, true);
}

#pragma clang diagnostic pop