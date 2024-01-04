#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Pointer_Type_Runner = Parser_Value_Runner<
    lloberon::Pointer_Type, &lloberon::Parser::parse_pointer_type
>;

TEST(Pointer_Type_Tests, empty) {
    lloberon::Scope scope;
    lloberon::Pointer_Type pointer_type { scope };
    Pointer_Type_Runner("", pointer_type, true);
}

TEST(Pointer_Type_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
       "Record", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::Pointer_Type pointer_type { scope };
    Pointer_Type_Runner("POINTER TO Record", pointer_type);
}

TEST(Pointer_Type_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "Record", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::Pointer_Type pointer_type { scope };
    Pointer_Type_Runner("POINTER TO", pointer_type, true);

    pointer_type.clear();
    Pointer_Type_Runner("POINTER Record", pointer_type, true, true);
}

#pragma clang diagnostic pop