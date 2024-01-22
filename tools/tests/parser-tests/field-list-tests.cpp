#include "parser-tests.h"

using Field_List_Runner = Parser_Arg_Void_Runner<
	type::Record, &Parser::parse_field_list
>;

TEST(Field_List_Tests, empty) {
	context::clear();
	type::Record field_list;
	Field_List_Runner test1 { "", field_list, true };
}

TEST(Field_List_Tests, simple) {
	context::clear();
	context::scope->register_base_types();
	type::Record record_type;
	Field_List_Runner test1 { "a: INTEGER", record_type };
	EXPECT_EQ(record_type.entries.size(), 1);
	const auto& first { record_type.entries[0] };
	EXPECT_STREQ(first.name.c_str(), "a");
	EXPECT_TRUE(first.type->is_integer());
	EXPECT_FALSE(first.exported);
}

TEST(Field_List_Tests, exported) {
	context::scope->register_base_types();
	type::Record field_list { };
	Field_List_Runner test1 { "a*: INTEGER", field_list };
	context::clear();
}

TEST(Field_List_Tests, multiple) {
	context::scope->register_base_types();
	type::Record field_list { };
	Field_List_Runner test1 { "a, b: INTEGER", field_list };
	context::clear();
}

TEST(Field_List_Tests, incomplete) {
	context::scope->register_base_types();
	type::Record field_list { };
	Field_List_Runner test1 { "a:", field_list, true };
	Field_List_Runner test2 { "a INTEGER", field_list, true, true };
	Field_List_Runner test3 { "a,:", field_list, true, true };
	context::clear();
}