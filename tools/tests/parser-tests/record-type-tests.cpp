#include "parser-tests.h"
#include "decl/type.h"

using Record_Type_Runner = Parser_Value_Runner<
    sema::Type, &Parser::parse_record_type
>;

TEST(Record_Type_Tests, empty) {
    Scope scope;
    sema::Type record_type { scope };
    Record_Type_Runner("", record_type, true);
}

TEST(Record_Type_Tests, simple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Type record_type { scope };
    Record_Type_Runner test1 { "RECORD END", record_type };
    auto record { std::dynamic_pointer_cast<type::Record>(record_type.type) };
    EXPECT_NE(record, nullptr);
    EXPECT_EQ(record->base, nullptr);

    record_type.clear();
    Record_Type_Runner test2 { "RECORD a: INTEGER END", record_type };
    record = std::dynamic_pointer_cast<type::Record>(record_type.type);
    EXPECT_NE(record, nullptr);
    EXPECT_EQ(record->base, nullptr);
    EXPECT_EQ(record->entries.size(), 1);
    const auto& first { record->entries[0] };
    EXPECT_STREQ(first.name.c_str(), "a");
    EXPECT_TRUE(first.type->is_integer());
    EXPECT_FALSE(first.exported);
}

TEST(Record_Type_Tests, sub_type) {
    Scope scope;
    auto view_record { std::make_shared<type::Record>() };
    auto point_record { std::make_shared<type::Record>() };
    scope.insert("View", std::make_shared<decl::Type>(view_record));
    scope.insert("Point", std::make_shared<decl::Type>(point_record));
    sema::Type record_type { scope };
    Record_Type_Runner test1 { "RECORD (View) END", record_type };
    auto record { std::dynamic_pointer_cast<type::Record>(record_type.type) };
    EXPECT_NE(record, nullptr);
    EXPECT_EQ(record->base, view_record);

    record_type.clear();
    Record_Type_Runner test2 { "RECORD (View) center*: Point END", record_type };
    record = std::dynamic_pointer_cast<type::Record>(record_type.type);
    EXPECT_NE(record, nullptr);
    EXPECT_EQ(record->base, view_record);
    EXPECT_EQ(record->entries.size(), 1);
    const auto& first { record->entries[0] };
    EXPECT_STREQ(first.name.c_str(), "center");
    EXPECT_EQ(first.type, point_record);
    EXPECT_TRUE(first.exported);
}