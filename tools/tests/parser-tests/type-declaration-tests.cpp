#include "parser-tests.h"
#include "decl/type.h"

using Type_Declaration_Runner = Parser_Value_Runner<sema::Type_Declaration, &Parser::parse_type_declaration>;

TEST(Type_Declaration_Tests, empty) {
    Scope scope;
    sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner test1 { "", type_declaration, true };
}

TEST(Type_Declaration_Tests, simple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner test1 { "a* = INTEGER", type_declaration };
}

TEST(Type_Declaration_Tests, incomplete) {
    Scope scope;
    sema::Type_Declaration type_declaration { scope };
    Type_Declaration_Runner test1 { "a =", type_declaration, true };

    type_declaration.clear();
    Type_Declaration_Runner test2 { "a", type_declaration, true };
}