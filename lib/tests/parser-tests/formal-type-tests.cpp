#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Type_Runner = Parser_Value_Runner<sema::Formal_Type, &Parser::parse_formal_type>;

TEST(Formal_Type_Tests, empty) {
    Scope scope;
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner("", formal_type, true);
}

TEST(Formal_Type_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner("INTEGER", formal_type);
}

TEST(Formal_Type_Tests, qualified) {
    Scope scope;
    auto module { new Module_Declaration {
        {}, "X", "X"
    }};
    module->insert(new Base_Type_Declaration {
        "Byte", Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner("X.Byte", formal_type);
}

TEST(Formal_Type_Tests, array) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner("ARRAY OF BYTE", formal_type);
}

TEST(Formal_Type_Tests, multiple_arrays) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Formal_Type formal_type { scope };
    Formal_Type_Runner("ARRAY OF ARRAY OF BYTE", formal_type);
}

#pragma clang diagnostic pop