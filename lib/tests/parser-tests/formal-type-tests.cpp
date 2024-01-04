#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Type_Runner = Parser_Value_Runner<lloberon::Formal_Type, &lloberon::Parser::parse_formal_type>;

TEST(Formal_Type_Tests, empty) {
    lloberon::Scope scope;
    lloberon::Formal_Type formal_type { scope };
    Formal_Type_Runner("", formal_type, true);
}

TEST(Formal_Type_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::Formal_Type formal_type { scope };
    Formal_Type_Runner("INTEGER", formal_type);
}

TEST(Formal_Type_Tests, qualified) {
    lloberon::Scope scope;
    auto module { new lloberon::Module_Declaration {
        {}, "X", "X"
    }};
    module->insert(new lloberon::Base_Type_Declaration {
        "Byte", lloberon::Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    lloberon::Formal_Type formal_type { scope };
    Formal_Type_Runner("X.Byte", formal_type);
}

TEST(Formal_Type_Tests, array) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::Formal_Type formal_type { scope };
    Formal_Type_Runner("ARRAY OF BYTE", formal_type);
}

TEST(Formal_Type_Tests, multiple_arrays) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::Formal_Type formal_type { scope };
    Formal_Type_Runner("ARRAY OF ARRAY OF BYTE", formal_type);
}

#pragma clang diagnostic pop