#include "parser-tests.h"

using Record_Type_Runner = Parser_Arg_Void_Runner<
	type::Type_Ptr, &Parser::parse_record_type
>;

TEST(Record_Type_Tests, empty) {
	type::Type_Ptr record_type;
	Record_Type_Runner("", record_type, true);
}

TEST(Record_Type_Tests, simple) {
	context::scope->register_base_types();
	type::Type_Ptr record_type;
	Record_Type_Runner test1 { "RECORD END", record_type };
	auto record { std::dynamic_pointer_cast<type::Record>(record_type) };
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, nullptr);

	Record_Type_Runner test2 { "RECORD a: INTEGER END", record_type };
	record = std::dynamic_pointer_cast<type::Record>(record_type);
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, nullptr);
	EXPECT_EQ(record->entries.size(), 1);
	const auto& first { record->entries[0] };
	EXPECT_STREQ(first.name.c_str(), "a");
	EXPECT_TRUE(first.type->is_integer());
	EXPECT_FALSE(first.exported);
	context::clear();
}

TEST(Record_Type_Tests, sub_type) {
	auto view_record { std::make_shared<type::Record>() };
	auto point_record { std::make_shared<type::Record>() };
	context::scope->insert("View", view_record);
	context::scope->insert("Point", point_record);
	type::Type_Ptr record_type;
	Record_Type_Runner test1 { "RECORD (View) END", record_type };
	auto record { std::dynamic_pointer_cast<type::Record>(record_type) };
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, view_record);

	Record_Type_Runner test2 {
		"RECORD (View) center*: Point END", record_type
	};
	record = std::dynamic_pointer_cast<type::Record>(record_type);
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, view_record);
	EXPECT_EQ(record->entries.size(), 1);
	const auto& first { record->entries[0] };
	EXPECT_STREQ(first.name.c_str(), "center");
	EXPECT_EQ(first.type, point_record);
	EXPECT_TRUE(first.exported);
	context::clear();
}