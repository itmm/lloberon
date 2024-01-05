#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Record_Type_Runner = Parser_Value_Runner<
    lloberon::sema::Record_Type, &Parser::parse_record_type
>;

TEST(Record_Type_Tests, empty) {
    Scope scope;
    lloberon::sema::Record_Type record_type { scope };
    Record_Type_Runner("", record_type, true);
}

TEST(Record_Type_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Record_Type record_type { scope };
    Record_Type_Runner("RECORD END", record_type);

    record_type.clear();
    Record_Type_Runner("RECORD a: INTEGER END", record_type);
}

TEST(Record_Type_Tests, sub_type) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "View", Base_Type_Declaration::bt_INTEGER
    });
    scope.insert(new Base_Type_Declaration {
            "Point", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Record_Type record_type { scope };
    Record_Type_Runner("RECORD (View) END", record_type);

    record_type.clear();
    Record_Type_Runner("RECORD (View) center: Point END", record_type);;
}

#pragma clang diagnostic pop