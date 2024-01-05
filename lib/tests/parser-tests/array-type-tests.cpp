#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Array_Type_Runner = Parser_Value_Runner<sema::Array_Type, &Parser::parse_array_type>;

TEST(Array_Type_Tests, empty) {
    Scope scope;
    sema::Array_Type array_type { scope };
    Array_Type_Runner("", array_type, true);
}

TEST(Array_Type_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Array_Type array_type { scope };
    Array_Type_Runner("ARRAY 3 OF BYTE", array_type);
}

TEST(Array_Type_Tests, multiple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Array_Type array_type { scope };
    Array_Type_Runner("ARRAY 3, 3 OF BYTE", array_type);
}

TEST(Array_Type_Tests, cascading) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Array_Type array_type { scope };
    Array_Type_Runner ("ARRAY 3 OF ARRAY 3 OF BYTE", array_type);
}

#pragma clang diagnostic pop