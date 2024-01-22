#include "parser-tests.h"

using Field_List_Sequence_Runner = Parser_Arg_Void_Runner<
	type::Record, &Parser::parse_field_list_sequence
>;

TEST(Field_List_Sequence_Tests, empty) {
	type::Record field_list_sequence;
	Field_List_Sequence_Runner test1 { "", field_list_sequence, true };
}

TEST(Field_List_Sequence_Tests, single) {
	context::scope->register_base_types();
	type::Record field_list_sequence;
	Field_List_Sequence_Runner test1 { "a: BYTE", field_list_sequence };
	context::clear();
}

TEST(Field_List_Sequence_Tests, multiple) {
	context::scope->register_base_types();
	type::Record field_list_sequence;
	Field_List_Sequence_Runner test1 {
		"a: BYTE; b: BYTE", field_list_sequence
	};
	context::clear();
}

TEST(Field_List_Sequence_Tests, incomplete) {
	context::scope->register_base_types();
	type::Record field_list_sequence;
	Field_List_Sequence_Runner test1 { "a: BYTE;", field_list_sequence, true };
	context::clear();
}