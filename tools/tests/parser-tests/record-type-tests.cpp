#include "parser-tests.h"

using Record_Type_Runner = Parser_No_Void_Runner<
	type::Record_Ptr, &Parser::parse_record_type
>;

TEST(Record_Type_Tests, empty) {
	Record_Type_Runner("", true);
}

TEST(Record_Type_Tests, simple) {
	context::scope->register_base_types();
	Record_Type_Runner test1 { "RECORD END" };
	auto record { std::dynamic_pointer_cast<type::Record>(test1.value) };
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, nullptr);

	Record_Type_Runner test2 { "RECORD a: INTEGER END" };
	record = std::dynamic_pointer_cast<type::Record>(test2.value);
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
	Record_Type_Runner test1 { "RECORD (View) END" };
	auto record { std::dynamic_pointer_cast<type::Record>(test1.value) };
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, view_record);

	Record_Type_Runner test2 { "RECORD (View) center*: Point END" };
	record = std::dynamic_pointer_cast<type::Record>(test2.value);
	EXPECT_NE(record, nullptr);
	EXPECT_EQ(record->base, view_record);
	EXPECT_EQ(record->entries.size(), 1);
	const auto& first { record->entries[0] };
	EXPECT_STREQ(first.name.c_str(), "center");
	EXPECT_EQ(first.type, point_record);
	EXPECT_TRUE(first.exported);
	context::clear();
}