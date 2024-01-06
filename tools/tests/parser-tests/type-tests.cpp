#include "parser-tests.h"

using Type_Runner = Parser_Value_Runner<sema::Type, &Parser::parse_type>;

TEST(Type_Tests, empty) {
    Scope scope;
    sema::Type type { scope };
    Type_Runner test1 { "", type, true };
}

TEST(Type_Tests, simple) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    scope.insert(std::make_shared<Base_Type_Declaration>(
        "Entry", Base_Type_Declaration::bt_INTEGER
    ));
    sema::Type type { scope };
    Type_Runner test1 { "INTEGER", type };
    Type_Runner test2 { "ARRAY 10 OF INTEGER", type };
    Type_Runner test3 { "RECORD x, y: INTEGER END", type };
    Type_Runner test4 { "POINTER TO Entry", type };
    Type_Runner test5 { "PROCEDURE (a: INTEGER): INTEGER", type };
}

TEST(Type_Tests, invalid) {
    Scope scope;
    sema::Type type { scope };
    Type_Runner test1 { ":", type, true, true };
}