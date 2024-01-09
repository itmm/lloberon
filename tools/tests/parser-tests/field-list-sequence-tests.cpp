#include "parser-tests.h"
#include "decl/type.h"

using Field_List_Sequence_Runner = Parser_Value_Runner<
    sema::Record_Type, &Parser::parse_field_list_sequence
>;

TEST(Field_List_Sequence_Tests, empty) {
    Scope scope;
    sema::Record_Type field_list_sequence { scope };
    Field_List_Sequence_Runner test1 { "", field_list_sequence, true };
}

TEST(Field_List_Sequence_Tests, single) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Record_Type field_list_sequence { scope };
    Field_List_Sequence_Runner test1 { "a: BYTE", field_list_sequence };
}

TEST(Field_List_Sequence_Tests, multiple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Record_Type field_list_sequence { scope };
    Field_List_Sequence_Runner test1 { "a: BYTE; b: BYTE", field_list_sequence };
}

TEST(Field_List_Sequence_Tests, incomplete) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Record_Type field_list_sequence { scope };
    Field_List_Sequence_Runner test1 { "a: BYTE;", field_list_sequence, true };
}