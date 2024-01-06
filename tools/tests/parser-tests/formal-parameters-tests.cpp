#include "parser-tests.h"

using Formal_Parameters_Runner = Parser_Value_Runner<
    sema::Formal_Parameters, &Parser::parse_formal_parameters
>;

TEST(Formal_Parameters_Tests, empty) {
    Scope scope;
    sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner("", formal_parameters, true);
}

TEST(Formal_Parameters_Tests, simple) {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);
    sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner test1 { "()", formal_parameters };

    formal_parameters.clear();
    Formal_Parameters_Runner test2 { "(VAR a: BYTE)", formal_parameters };
}

TEST(Formal_Parameters_Tests, with_return) {
    Scope scope;
    auto module = std::make_shared<Module_Declaration>(llvm::SMLoc {}, "X", "X");
    module->insert(std::make_shared<Base_Type_Declaration>(
        "Byte", Base_Type_Declaration::bt_BYTE
    ));
    scope.insert(module);
    sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner test1 { "(): X.Byte", formal_parameters };
}

TEST(Formal_Parameters_Tests, incomplete) {
    Scope scope;
    sema::Formal_Parameters formal_parameters { scope };
    Formal_Parameters_Runner test1 { "(", formal_parameters, true };

    formal_parameters.clear();
    Formal_Parameters_Runner test2 { "():", formal_parameters, true };
}