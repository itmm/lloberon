#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Type_Runner = Parser_Value_Runner<lloberon::sema::Type, &Parser::parse_type>;

TEST(Type_Tests, empty) {
    Scope scope;
    lloberon::sema::Type type { scope };
    Type_Runner("", type, true);
}

TEST(Type_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    scope.insert(new Base_Type_Declaration {
        "Entry", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Type type { scope };
    Type_Runner("INTEGER", type);
    Type_Runner("ARRAY 10 OF INTEGER", type);
    Type_Runner("RECORD x, y: INTEGER END", type);
    Type_Runner("POINTER TO Entry", type);
    Type_Runner("PROCEDURE (a: INTEGER): INTEGER", type);
}

TEST(Type_Tests, invalid) {
    Scope scope;
    lloberon::sema::Type type { scope };
    Type_Runner(":", type, true, true);
}

#pragma clang diagnostic pop