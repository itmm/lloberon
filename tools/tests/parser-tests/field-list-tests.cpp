#include "parser-tests.h"
#include "decl/type.h"

using Field_List_Runner = Parser_Value_Runner<
    sema::Field_List, &Parser::parse_field_list
>;

TEST(Field_List_Tests, empty) {
    Scope scope;
    sema::Field_List field_list { scope };
    Field_List_Runner test1 { "", field_list, true };
}

TEST(Field_List_Tests, simple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Field_List field_list { scope };
    Field_List_Runner test1 { "a: INTEGER", field_list };
}

TEST(Field_List_Tests, exported) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Field_List field_list { scope };
    Field_List_Runner test1 { "a*: INTEGER", field_list };
}

TEST(Field_List_Tests, multiple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Field_List field_list { scope };
    Field_List_Runner test1 { "a, b: INTEGER", field_list };
}

TEST(Field_List_Tests, incomplete) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Field_List field_list { scope };
    Field_List_Runner test1 { "a:", field_list, true };

    field_list.clear();
    Field_List_Runner test2 { "a INTEGER", field_list, true, true };

    field_list.clear();
    Field_List_Runner test3 { "a,:", field_list, true, true };
}