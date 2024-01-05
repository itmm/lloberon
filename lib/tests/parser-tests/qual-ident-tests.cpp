#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Qual_Ident_Runner = Parser_Value_Runner<lloberon::sema::Qual_Ident, &Parser::parse_qual_ident>;

TEST(Qual_Ident_Tests, empty) {
    Scope scope;
    lloberon::sema::Qual_Ident qual_ident { scope };
    Qual_Ident_Runner("", qual_ident, true);
}

TEST(Qual_Ident_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration(
        "BYTE", Base_Type_Declaration::bt_BYTE
    ));
    lloberon::sema::Qual_Ident qual_ident { scope };
    Qual_Ident_Runner("BYTE", qual_ident);
    qual_ident.clear();
    new (&scope) Scope { };
    auto module = new Module_Declaration({}, "X", "X");
    scope.insert(module);
    module->insert(new Base_Type_Declaration(
        "Byte", Base_Type_Declaration::bt_BYTE
    ));
    Qual_Ident_Runner("X.Byte", qual_ident);
}

TEST(Qual_Ident_Tests, incomplete) {
    Scope scope;
    lloberon::sema::Qual_Ident qual_ident { scope };
    auto module = new Module_Declaration({}, "X", "X");
    scope.insert(module);
    Qual_Ident_Runner("X.", qual_ident, true);
    qual_ident.clear();
    Qual_Ident_Runner(".", qual_ident, true, true);
}

#pragma clang diagnostic pop