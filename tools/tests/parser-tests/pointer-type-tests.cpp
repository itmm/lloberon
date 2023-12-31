#include "parser-tests.h"
#include "decl/type.h"
#include "type/base.h"
#include "type/pointer.h"

using Pointer_Type_Runner = Parser_Value_Runner<
    sema::Type, &Parser::parse_pointer_type
>;

TEST(Pointer_Type_Tests, empty) {
    Scope scope;
    sema::Type pointer_type { scope };
    Pointer_Type_Runner test1 { "", pointer_type, true };
}

TEST(Pointer_Type_Tests, simple) {
    Scope scope;
    scope.insert("Record", std::make_shared<decl::Type>(
       std::make_shared<type::Base>(type::Base::bt_INTEGER)
    ));
    sema::Type pointer_type { scope };
    Pointer_Type_Runner test1 { "POINTER TO Record", pointer_type };
    EXPECT_NE(std::dynamic_pointer_cast<type::Pointer>(pointer_type.type), nullptr);
}

TEST(Pointer_Type_Tests, incomplete) {
    Scope scope;
    scope.insert("Record", std::make_shared<decl::Type>(
        std::make_shared<type::Base>(type::Base::bt_INTEGER)
    ));
    sema::Type pointer_type { scope };
    Pointer_Type_Runner test1 { "POINTER TO", pointer_type, true };

    pointer_type.clear();
    Pointer_Type_Runner test2 { "POINTER Record", pointer_type, true, true };
}