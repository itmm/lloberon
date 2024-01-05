#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Array_Type_Runner = Parser_Value_Runner<lloberon::sema::Array_Type, &lloberon::Parser::parse_array_type>;

TEST(Array_Type_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Array_Type array_type { scope };
    Array_Type_Runner("", array_type, true);
}

TEST(Array_Type_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Array_Type array_type { scope };
    Array_Type_Runner("ARRAY 3 OF BYTE", array_type);
}

TEST(Array_Type_Tests, multiple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Array_Type array_type { scope };
    Array_Type_Runner("ARRAY 3, 3 OF BYTE", array_type);
}

TEST(Array_Type_Tests, cascading) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Array_Type array_type { scope };
    Array_Type_Runner ("ARRAY 3 OF ARRAY 3 OF BYTE", array_type);
}

#pragma clang diagnostic pop