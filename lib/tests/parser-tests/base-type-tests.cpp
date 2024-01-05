#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Base_Type_Runner = Parser_Value_Runner<lloberon::sema::Base_Type, &lloberon::Parser::parse_base_type>;

TEST(Base_Type_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Base_Type base_type { scope };
    Base_Type_Runner("", base_type, true);
}

TEST(Base_Type_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Base_Type base_type { scope };
    Base_Type_Runner("BYTE", base_type);
}

TEST(Base_Type_Tests, qualified) {
    lloberon::Scope scope;
    auto module = new lloberon::Module_Declaration {
        {}, "X", "X"
    };
    module->insert(new lloberon::Base_Type_Declaration {
        "Byte", lloberon::Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    lloberon::sema::Base_Type base_type { scope };
    Base_Type_Runner("X.Byte", base_type);
}

#pragma clang diagnostic pop