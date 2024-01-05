#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Base_Type_Runner = Parser_Value_Runner<sema::Base_Type, &Parser::parse_base_type>;

TEST(Base_Type_Tests, empty) {
    Scope scope;
    sema::Base_Type base_type { scope };
    Base_Type_Runner("", base_type, true);
}

TEST(Base_Type_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Base_Type base_type { scope };
    Base_Type_Runner("BYTE", base_type);
}

TEST(Base_Type_Tests, qualified) {
    Scope scope;
    auto module = new Module_Declaration {
        {}, "X", "X"
    };
    module->insert(new Base_Type_Declaration {
        "Byte", Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    sema::Base_Type base_type { scope };
    Base_Type_Runner("X.Byte", base_type);
}

#pragma clang diagnostic pop