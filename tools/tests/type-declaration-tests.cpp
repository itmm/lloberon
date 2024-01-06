#include "gtest/gtest.h"
#include "decl/base-type.h"

template<decl::Base_Type::Kind KIND>
class Base_Type_Declaration_Test: public testing::Test {
protected:
    decl::Base_Type decl {
        "", decl::Base_Type::bt_BYTE
    };

    void SetUp() override {
        new (&decl) decl::Base_Type {"INTEGER", KIND };
    }
};


using Boolean_Type_Declaration_Test = Base_Type_Declaration_Test<
        decl::Base_Type::bt_BOOLEAN
>;

TEST_F(Boolean_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), decl::Base_Type::bt_BOOLEAN);
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
    decl::Base_Type::bt_CHAR
>;

TEST_F(Char_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), decl::Base_Type::bt_CHAR);
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
    decl::Base_Type::bt_INTEGER
>;

TEST_F(Integer_Type_Declaration_Test, kind) {
    EXPECT_EQ(decl.kind(), decl::Declaration::DK_Type);
}

TEST_F(Integer_Type_Declaration_Test, name) {
    EXPECT_STREQ(decl.name().c_str(), "INTEGER");
}

TEST_F(Integer_Type_Declaration_Test, no_enclosing_decl) {
    EXPECT_EQ(decl.enclosing_declaration(), nullptr);
}

TEST_F(Integer_Type_Declaration_Test, class_of) {
    EXPECT_TRUE(decl::Type::classof(&decl));
}

TEST_F(Integer_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), decl::Base_Type::bt_INTEGER);
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
    decl::Base_Type::bt_REAL
>;

TEST_F(Real_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), decl::Base_Type::bt_REAL);
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

using Byte_Type_Declaration_Test = Base_Type_Declaration_Test<
    decl::Base_Type::bt_BYTE
>;

TEST_F(Byte_Type_Declaration_Test, base_kind) {
    EXPECT_EQ(decl.base_kind(), decl::Base_Type::bt_BYTE);
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
