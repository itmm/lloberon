#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Parameter_Section_Runner = Parser_Value_Runner<
    lloberon::sema::Formal_Parameter_Section, &Parser::parse_formal_parameter_section
>;

TEST(Formal_Parameter_Section_Tests, empty) {
    Scope scope;
    lloberon::sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner("", formal_parameter_section, true);
}

TEST(Formal_Parameter_Section_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner("a: ARRAY OF INTEGER", formal_parameter_section);
}

TEST(Formal_Parameter_Section_Tests, multiple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner("a, b: INTEGER", formal_parameter_section);
}

TEST(Formal_Parameter_Section_Tests, var_parameter) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner("VAR a: INTEGER", formal_parameter_section);
}

TEST(Formal_Parameter_Section_Tests, incomplete) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    lloberon::sema::Formal_Parameter_Section formal_parameter_section { scope };
    Formal_Parameter_Section_Runner("VAR", formal_parameter_section, true);

    formal_parameter_section.clear();
    Formal_Parameter_Section_Runner("a,", formal_parameter_section, true);

    formal_parameter_section.clear();
    Formal_Parameter_Section_Runner("a INTEGER", formal_parameter_section, true, true);
}

#pragma clang diagnostic pop