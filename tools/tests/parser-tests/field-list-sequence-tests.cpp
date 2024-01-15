#include "parser-tests.h"
#include "decl/type.h"

using Field_List_Sequence_Runner = Parser_Value_Runner<
	sema::Record_Type, &Parser::parse_field_list_sequence
>;

TEST(Field_List_Sequence_Tests, empty) {
	Context context;
	sema::Record_Type field_list_sequence { context };
	Field_List_Sequence_Runner test1 { "", field_list_sequence, true };
}

TEST(Field_List_Sequence_Tests, single) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	sema::Record_Type field_list_sequence { context };
	Field_List_Sequence_Runner test1 { "a: BYTE", field_list_sequence };
}

TEST(Field_List_Sequence_Tests, multiple) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	sema::Record_Type field_list_sequence { context };
	Field_List_Sequence_Runner test1 {
		"a: BYTE; b: BYTE", field_list_sequence
	};
}

TEST(Field_List_Sequence_Tests, incomplete) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	sema::Record_Type field_list_sequence { context };
	Field_List_Sequence_Runner test1 { "a: BYTE;", field_list_sequence, true };
	EXPECT_EQ(field_list_sequence.record->entries.size(), 0);
}