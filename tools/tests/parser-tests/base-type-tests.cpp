#include "parser-tests.h"
#include "decl/base-type.h"

using Base_Type_Runner = Parser_Value_Runner<sema::Base_Type, &Parser::parse_base_type>;

TEST(Base_Type_Tests, empty) {
    Scope scope;
    sema::Base_Type base_type { scope };
    Base_Type_Runner("", base_type, true);
}

TEST(Base_Type_Tests, simple) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    sema::Base_Type base_type { scope };
    Base_Type_Runner test1 ("BYTE", base_type);
}

TEST(Base_Type_Tests, qualified) {
    Scope scope;
    auto module = std::make_shared<decl::Module>(
        llvm::SMLoc {}, "X", "X"
    );
    module->insert(std::make_shared<decl::Base_Type>(
        "Byte", decl::Base_Type::bt_BYTE
    ));
    scope.insert(module);
    sema::Base_Type base_type { scope };
    Base_Type_Runner test1 { "X.Byte", base_type };
}