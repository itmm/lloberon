#include "gtest/gtest.h"
#include "lloberon/ast/declaration.h"

template<lloberon::Base_Type_Declaration::Kind KIND>
class Base_Type_Declaration_Test: public testing::Test {
protected:
    lloberon::Base_Type_Declaration decl {
        "", lloberon::Base_Type_Declaration::bt_BYTE
    };

    void SetUp() override {
        new (&decl) lloberon::Base_Type_Declaration { "INTEGER", KIND };
    }
};


using Boolean_Type_Declaration_Test = Base_Type_Declaration_Test<
        lloberon::Base_Type_Declaration::bt_BOOLEAN
>;

TEST_F(Boolean_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), lloberon::Base_Type_Declaration::bt_BOOLEAN);
}

TEST_F(Boolean_Type_Declaration_Test, is_bool) {
    EXPECT_TRUE(decl.is_bool());
}

TEST_F(Boolean_Type_Declaration_Test, is_numeric) {
    EXPECT_FALSE(decl.is_numeric());
}

TEST_F(Boolean_Type_Declaration_Test, is_integer) {
    EXPECT_FALSE(decl.is_integer());
}

using Char_Type_Declaration_Test = Base_Type_Declaration_Test<
    lloberon::Base_Type_Declaration::bt_CHAR
>;

TEST_F(Char_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), lloberon::Base_Type_Declaration::bt_CHAR);
}

TEST_F(Char_Type_Declaration_Test, is_bool) {
    EXPECT_FALSE(decl.is_bool());
}

TEST_F(Char_Type_Declaration_Test, is_numeric) {
    EXPECT_FALSE(decl.is_numeric());
}

TEST_F(Char_Type_Declaration_Test, is_integer) {
    EXPECT_FALSE(decl.is_integer());
}

using Integer_Type_Declaration_Test = Base_Type_Declaration_Test<
    lloberon::Base_Type_Declaration::bt_INTEGER
>;

TEST_F(Integer_Type_Declaration_Test, kind) {
    EXPECT_EQ(decl.kind(), lloberon::Declaration::DK_Type);
}

TEST_F(Integer_Type_Declaration_Test, name) {
    EXPECT_STREQ(decl.name().c_str(), "INTEGER");
}

TEST_F(Integer_Type_Declaration_Test, no_enclosing_decl) {
    EXPECT_EQ(decl.enclosing_declaration(), nullptr);
}

TEST_F(Integer_Type_Declaration_Test, class_of) {
    EXPECT_TRUE(lloberon::Type_Declaration::classof(&decl));
}

TEST_F(Integer_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), lloberon::Base_Type_Declaration::bt_INTEGER);
}

TEST_F(Integer_Type_Declaration_Test, is_bool) {
    EXPECT_FALSE(decl.is_bool());
}

TEST_F(Integer_Type_Declaration_Test, is_numeric) {
    EXPECT_TRUE(decl.is_numeric());
}

TEST_F(Integer_Type_Declaration_Test, is_integer) {
    EXPECT_TRUE(decl.is_integer());
}

using Real_Type_Declaration_Test = Base_Type_Declaration_Test<
        lloberon::Base_Type_Declaration::bt_REAL
>;

TEST_F(Real_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), lloberon::Base_Type_Declaration::bt_REAL);
}

TEST_F(Real_Type_Declaration_Test, is_bool) {
    EXPECT_FALSE(decl.is_bool());
}

TEST_F(Real_Type_Declaration_Test, is_numeric) {
    EXPECT_TRUE(decl.is_numeric());
}

TEST_F(Real_Type_Declaration_Test, is_integer) {
    EXPECT_FALSE(decl.is_integer());
}

// enum Kind { bt_BYTE, bt_SET };

using Byte_Type_Declaration_Test = Base_Type_Declaration_Test<
        lloberon::Base_Type_Declaration::bt_BYTE
>;

TEST_F(Byte_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), lloberon::Base_Type_Declaration::bt_BYTE);
}

TEST_F(Byte_Type_Declaration_Test, is_bool) {
    EXPECT_FALSE(decl.is_bool());
}

TEST_F(Byte_Type_Declaration_Test, is_numeric) {
    EXPECT_TRUE(decl.is_numeric());
}

TEST_F(Byte_Type_Declaration_Test, is_integer) {
    EXPECT_TRUE(decl.is_integer());
}
