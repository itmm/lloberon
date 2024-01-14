#include "parser-tests.h"
#include "decl/type.h"

using Field_List_Runner = Parser_Value_Runner<
	sema::Record_Type, &Parser::parse_field_list
>;

TEST(Field_List_Tests, empty) {
	Scope scope;
	sema::Record_Type field_list { scope };
	Field_List_Runner test1 { "", field_list, true };
}

TEST(Field_List_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Record_Type record_type { scope };
	Field_List_Runner test1 { "a: INTEGER", record_type };
	EXPECT_EQ(record_type.record->entries.size(), 1);
	const auto& first { record_type.record->entries[0] };
	EXPECT_STREQ(first.name.c_str(), "a");
	EXPECT_TRUE(first.type->is_integer());
	EXPECT_FALSE(first.exported);
}

TEST(Field_List_Tests, exported) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Record_Type field_list { scope };
	Field_List_Runner test1 { "a*: INTEGER", field_list };
}

TEST(Field_List_Tests, multiple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Record_Type field_list { scope };
	Field_List_Runner test1 { "a, b: INTEGER", field_list };
}

TEST(Field_List_Tests, incomplete) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Record_Type field_list { scope };
	Field_List_Runner test1 { "a:", field_list, true };
	Field_List_Runner test2 { "a INTEGER", field_list, true, true };
	Field_List_Runner test3 { "a,:", field_list, true, true };
}