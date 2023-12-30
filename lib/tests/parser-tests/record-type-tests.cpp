#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Record_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_record_type>;

TEST(Record_Type_Tests, empty) {
    Record_Type_Runner("", true);
}

TEST(Record_Type_Tests, simple) {
    Record_Type_Runner("RECORD END");
    Record_Type_Runner("RECORD a: INTEGER END");
}

TEST(Record_Type_Tests, sub_type) {
    Record_Type_Runner("RECORD (View) END");
    Record_Type_Runner("RECORD (View) center: Point END");;
}

#pragma clang diagnostic pop