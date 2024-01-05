#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Parameters_Runner = Parser_Value_Runner<
    lloberon::sema::Formal_Parameters, &lloberon::Parser::parse_formal_parameters
>;

TEST(Formal_Parameters_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("", formal_parameters, true);
}

TEST(Formal_Parameters_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "BYTE", lloberon::Base_Type_Declaration::bt_BYTE
    });
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("()", formal_parameters);

    formal_parameters.clear();
    Formal_Parameters_Runner("(VAR a: BYTE)", formal_parameters);
}

TEST(Formal_Parameters_Tests, with_return) {
    lloberon::Scope scope;
    auto module = new lloberon::Module_Declaration { {}, "X", "X" };
    module->insert(new lloberon::Base_Type_Declaration {
        "Byte", lloberon::Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("(): X.Byte", formal_parameters);
}

TEST(Formal_Parameters_Tests, incomplete) {
    lloberon::Scope scope;
    lloberon::sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("(", formal_parameters, true);
    Formal_Parameters_Runner("():", formal_parameters, true);
}

#pragma clang diagnostic pop