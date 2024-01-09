#include "parser-tests.h"
#include "decl/type.h"
#include "type/base.h"

using Record_Type_Runner = Parser_Value_Runner<
    sema::Record_Type, &Parser::parse_record_type
>;

TEST(Record_Type_Tests, empty) {
    Scope scope;
    sema::Record_Type record_type { scope };
    Record_Type_Runner("", record_type, true);
}

TEST(Record_Type_Tests, simple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Record_Type record_type { scope };
    Record_Type_Runner test1 { "RECORD END", record_type };

    record_type.clear();
    Record_Type_Runner test2 { "RECORD a: INTEGER END", record_type };
}

TEST(Record_Type_Tests, sub_type) {
    Scope scope;
    scope.insert("View", std::make_shared<decl::Type>(
        std::make_shared<type::Base>(type::Base::bt_INTEGER)
    ));
    scope.insert("Point", std::make_shared<decl::Type>(
        std::make_shared<type::Base>(type::Base::bt_INTEGER)
    ));
    sema::Record_Type record_type { scope };
    Record_Type_Runner test1 { "RECORD (View) END", record_type };

    record_type.clear();
    Record_Type_Runner test2 { "RECORD (View) center: Point END", record_type };
}