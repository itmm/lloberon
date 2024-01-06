#include "parser-tests.h"

using Array_Type_Runner = Parser_Value_Runner<sema::Array_Type, &Parser::parse_array_type>;

TEST(Array_Type_Tests, empty) {
    Scope scope;
    sema::Array_Type array_type { scope };
    Array_Type_Runner test1 { "", array_type, true };
}

TEST(Array_Type_Tests, simple) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Array_Type array_type { scope };
    Array_Type_Runner test1 { "ARRAY 3 OF BYTE", array_type };
}

TEST(Array_Type_Tests, multiple) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Array_Type array_type { scope };
    Array_Type_Runner test1 { "ARRAY 3, 3 OF BYTE", array_type };
}

TEST(Array_Type_Tests, cascading) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Array_Type array_type { scope };
    Array_Type_Runner test1 { "ARRAY 3 OF ARRAY 3 OF BYTE", array_type };
}