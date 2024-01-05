#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Field_List_Runner = Parser_Value_Runner<
    lloberon::sema::Field_List, &lloberon::Parser::parse_field_list
>;

TEST(Field_List_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Field_List field_list { scope };
    Field_List_Runner("", field_list, true);
}

TEST(Field_List_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration{
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Field_List field_list { scope };
    Field_List_Runner("a: INTEGER", field_list);
}

TEST(Field_List_Tests, exported) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration{
            "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Field_List field_list { scope };
    Field_List_Runner("a*: INTEGER", field_list);
}

TEST(Field_List_Tests, multiple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration{
            "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Field_List field_list { scope };
    Field_List_Runner("a, b: INTEGER", field_list);
}

TEST(Field_List_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration{
            "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Field_List field_list { scope };
    Field_List_Runner("a:", field_list, true);

    field_list.clear();
    Field_List_Runner("a INTEGER", field_list, true, true);

    field_list.clear();
    Field_List_Runner("a,:", field_list, true, true);
}

#pragma clang diagnostic pop