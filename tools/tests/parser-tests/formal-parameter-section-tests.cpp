#include "parser-tests.h"
#include "decl/base-type.h"

using Formal_Parameter_Section_Runner = Parser_Value_Runner<
    sema::Formal_Parameter_Section, &Parser::parse_formal_parameter_section
>;

TEST(Formal_Parameter_Section_Tests, empty) {
    Scope scope;
    sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner("", formal_parameter_section, true);
}

TEST(Formal_Parameter_Section_Tests, simple) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner test1 { "a: ARRAY OF INTEGER", formal_parameter_section };
}

TEST(Formal_Parameter_Section_Tests, multiple) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner test1 { "a, b: INTEGER", formal_parameter_section };
}

TEST(Formal_Parameter_Section_Tests, var_parameter) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner test1 { "VAR a: INTEGER", formal_parameter_section };
}

TEST(Formal_Parameter_Section_Tests, incomplete) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner test1 { "VAR", formal_parameter_section, true };

    formal_parameter_section.clear();
    Formal_Parameter_Section_Runner test2 { "a,", formal_parameter_section, true };

    formal_parameter_section.clear();
    Formal_Parameter_Section_Runner test3 { "a INTEGER", formal_parameter_section, true, true };
}