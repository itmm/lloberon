#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Field_List_Runner = Parser_Value_Runner<
    sema::Field_List, &Parser::parse_field_list
>;

TEST(Field_List_Tests, empty) {
    Scope scope;
    sema::Field_List field_list { scope };
    Field_List_Runner("", field_list, true);
}

TEST(Field_List_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration{
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Field_List field_list { scope };
    Field_List_Runner("a: INTEGER", field_list);
}

TEST(Field_List_Tests, exported) {
    Scope scope;
    scope.insert(new Base_Type_Declaration{
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Field_List field_list { scope };
    Field_List_Runner("a*: INTEGER", field_list);
}

TEST(Field_List_Tests, multiple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration{
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Field_List field_list { scope };
    Field_List_Runner("a, b: INTEGER", field_list);
}

TEST(Field_List_Tests, incomplete) {
    Scope scope;
    scope.insert(new Base_Type_Declaration{
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Field_List field_list { scope };
    Field_List_Runner("a:", field_list, true);

    field_list.clear();
    Field_List_Runner("a INTEGER", field_list, true, true);

    field_list.clear();
    Field_List_Runner("a,:", field_list, true, true);
}

#pragma clang diagnostic pop