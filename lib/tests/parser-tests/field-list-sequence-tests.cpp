#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Field_List_Sequence_Runner = Parser_Value_Runner<
    sema::Field_List_Sequence, &Parser::parse_field_list_sequence
>;

TEST(Field_List_Sequence_Tests, empty) {
    Scope scope;
    sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("", field_list_sequence, true);
}

TEST(Field_List_Sequence_Tests, single) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("a: BYTE", field_list_sequence);
}

TEST(Field_List_Sequence_Tests, multiple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("a: BYTE; b: BYTE", field_list_sequence);
}

TEST(Field_List_Sequence_Tests, incomplete) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("a: BYTE;", field_list_sequence, true);
}

#pragma clang diagnostic pop