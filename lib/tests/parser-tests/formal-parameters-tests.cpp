#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Parameters_Runner = Parser_Value_Runner<
    lloberon::sema::Formal_Parameters, &Parser::parse_formal_parameters
>;

TEST(Formal_Parameters_Tests, empty) {
    Scope scope;
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("", formal_parameters, true);
}

TEST(Formal_Parameters_Tests, simple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "BYTE", Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("()", formal_parameters);

    formal_parameters.clear();
    Formal_Parameters_Runner("(VAR a: BYTE)", formal_parameters);
}

TEST(Formal_Parameters_Tests, with_return) {
    Scope scope;
    auto module = new Module_Declaration { {}, "X", "X" };
    module->insert(new Base_Type_Declaration {
        "Byte", Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("(): X.Byte", formal_parameters);
}

TEST(Formal_Parameters_Tests, incomplete) {
    Scope scope;
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("(", formal_parameters, true);
    Formal_Parameters_Runner("():", formal_parameters, true);
}

#pragma clang diagnostic pop