#include "parser-tests.h"

using Formal_Type_Runner = Parser_Value_Runner<sema::Formal_Type, &Parser::parse_formal_type>;

TEST(Formal_Type_Tests, empty) {
    Scope scope;
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner test1 { "", formal_type, true };
}

TEST(Formal_Type_Tests, simple) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner test1 { "INTEGER", formal_type };
}

TEST(Formal_Type_Tests, qualified) {
    Scope scope;
    auto module { std::make_shared<Module_Declaration>(
        llvm::SMLoc {}, "X", "X"
    ) };
    module->insert(std::make_shared<Base_Type_Declaration>(
        "Byte", Base_Type_Declaration::bt_BYTE
    ));
    scope.insert(module);
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner test1 { "X.Byte", formal_type };
}

TEST(Formal_Type_Tests, array) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner test1 { "ARRAY OF BYTE", formal_type };
}

TEST(Formal_Type_Tests, multiple_arrays) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner test1 { "ARRAY OF ARRAY OF BYTE", formal_type };
}