#include "parser-tests.h"
#include "decl/type.h"
#include "type/base.h"

using Type_Runner = Parser_Value_Runner<sema::Type, &Parser::parse_type>;

TEST(Type_Tests, empty) {
    Scope scope;
    sema::Type type { scope };
    Type_Runner test1 { "", type, true };
}

TEST(Type_Tests, simple) {
    Scope scope;
    decl::Type::register_base_types(scope);
    scope.insert(std::make_shared<decl::Type>(
        nullptr, llvm::SMLoc { }, "Entry",
        std::make_shared<type::Base>(type::Base::bt_INTEGER)
    ));
    sema::Type type { scope };
    Type_Runner test1 { "BOOLEAN", type };
    EXPECT_STREQ(type.type->name().c_str(), "BOOLEAN");

    Type_Runner test2 { "CHAR", type };
    EXPECT_STREQ(type.type->name().c_str(), "CHAR");

    Type_Runner test3 { "INTEGER", type };
    EXPECT_STREQ(type.type->name().c_str(), "INTEGER");

    Type_Runner test4 { "REAL", type };
    EXPECT_STREQ(type.type->name().c_str(), "REAL");

    Type_Runner test5 { "BYTE", type };
    EXPECT_STREQ(type.type->name().c_str(), "BYTE");

    Type_Runner test6 { "SET", type };
    EXPECT_STREQ(type.type->name().c_str(), "SET");

    Type_Runner test7 { "ARRAY 10 OF INTEGER", type };
    Type_Runner test8 { "RECORD x, y: INTEGER END", type };
    Type_Runner test9 { "POINTER TO Entry", type };
    Type_Runner test10 { "PROCEDURE (a: INTEGER): INTEGER", type };
}

TEST(Type_Tests, invalid) {
    Scope scope;
    sema::Type type { scope };
    Type_Runner test1 { ":", type, true, true };
}