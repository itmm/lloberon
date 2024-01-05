#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Field_List_Sequence_Runner = Parser_Value_Runner<
    lloberon::sema::Field_List_Sequence, &lloberon::Parser::parse_field_list_sequence
>;

TEST(Field_List_Sequence_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("", field_list_sequence, true);
}

TEST(Field_List_Sequence_Tests, single) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("a: BYTE", field_list_sequence);
}

TEST(Field_List_Sequence_Tests, multiple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("a: BYTE; b: BYTE", field_list_sequence);
}

TEST(Field_List_Sequence_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Field_List_Sequence field_list_sequence { scope };
    Field_List_Sequence_Runner("a: BYTE;", field_list_sequence, true);
}

#pragma clang diagnostic pop