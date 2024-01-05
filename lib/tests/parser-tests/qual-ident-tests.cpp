#include "parser-tests.h"

using Qual_Ident_Runner = Parser_Value_Runner<sema::Qual_Ident, &Parser::parse_qual_ident>;

TEST(Qual_Ident_Tests, empty) {
    Scope scope;
    sema::Qual_Ident qual_ident { scope };
    Qual_Ident_Runner test1 { "", qual_ident, true };
}

TEST(Qual_Ident_Tests, simple) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Qual_Ident qual_ident { scope };
    Qual_Ident_Runner test1 { "BYTE", qual_ident };
    qual_ident.clear();
    new (&scope) Scope { };
    auto module = std::make_shared<Module_Declaration>(llvm::SMLoc {}, "X", "X");
    scope.insert(module);
    module->insert(std::make_shared<Base_Type_Declaration>(
        "Byte", Base_Type_Declaration::bt_BYTE
    ));
    Qual_Ident_Runner test2 { "X.Byte", qual_ident };
}

TEST(Qual_Ident_Tests, incomplete) {
    Scope scope;
    sema::Qual_Ident qual_ident { scope };
    auto module = std::make_shared<Module_Declaration>(llvm::SMLoc {}, "X", "X");
    scope.insert(module);
    Qual_Ident_Runner test1 { "X.", qual_ident, true };

    qual_ident.clear();
    Qual_Ident_Runner test2 { ".", qual_ident, true, true };
}