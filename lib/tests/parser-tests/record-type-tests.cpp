#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Record_Type_Runner = Parser_Value_Runner<
    lloberon::Record_Type, &lloberon::Parser::parse_record_type
>;

TEST(Record_Type_Tests, empty) {
    lloberon::Scope scope;
    lloberon::Record_Type record_type { scope };
    Record_Type_Runner("", record_type, true);
}

TEST(Record_Type_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::Record_Type record_type { scope };
    Record_Type_Runner("RECORD END", record_type);

    record_type.clear();
    Record_Type_Runner("RECORD a: INTEGER END", record_type);
}

TEST(Record_Type_Tests, sub_type) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
            "View", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    scope.insert(new lloberon::Base_Type_Declaration {
            "Point", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    lloberon::Record_Type record_type { scope };
    Record_Type_Runner("RECORD (View) END", record_type);

    record_type.clear();
    Record_Type_Runner("RECORD (View) center: Point END", record_type);;
}

#pragma clang diagnostic pop