#include "gtest/gtest.h"
#include "type/base.h"

template<type::Base::Kind KIND>
class Base_Type_Declaration_Test : public testing::Test {
protected:
	type::Base type { type::Base::bt_BYTE };

	void SetUp() override {
		new(&type) type::Base { KIND };
	}
};


using Boolean_Type_Declaration_Test = Base_Type_Declaration_Test<
	type::Base::bt_BOOLEAN
>;

TEST_F(Boolean_Type_Declaration_Test, base_kind) {
	EXPECT_EQ(type.base_kind(), type::Base::bt_BOOLEAN);
}

TEST_F(Boolean_Type_Declaration_Test, is_bool) {
	EXPECT_TRUE(type.is_bool());
}

TEST_F(Boolean_Type_Declaration_Test, is_numeric) {
	EXPECT_FALSE(type.is_numeric());
}

TEST_F(Boolean_Type_Declaration_Test, is_integer) {
	EXPECT_FALSE(type.is_integer());
}

using Char_Type_Declaration_Test = Base_Type_Declaration_Test<
	type::Base::bt_CHAR
>;

TEST_F(Char_Type_Declaration_Test, base_kind) {
	EXPECT_EQ(type.base_kind(), type::Base::bt_CHAR);
}

TEST_F(Char_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type.is_bool());
}

TEST_F(Char_Type_Declaration_Test, is_numeric) {
	EXPECT_FALSE(type.is_numeric());
}

TEST_F(Char_Type_Declaration_Test, is_integer) {
	EXPECT_FALSE(type.is_integer());
}

using Integer_Type_Declaration_Test = Base_Type_Declaration_Test<
	type::Base::bt_INTEGER
>;

TEST_F(Integer_Type_Declaration_Test, base_kind) {
	EXPECT_EQ(type.base_kind(), type::Base::bt_INTEGER);
}

TEST_F(Integer_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type.is_bool());
}

TEST_F(Integer_Type_Declaration_Test, is_numeric) {
	EXPECT_TRUE(type.is_numeric());
}

TEST_F(Integer_Type_Declaration_Test, is_integer) {
	EXPECT_TRUE(type.is_integer());
}

using Real_Type_Declaration_Test = Base_Type_Declaration_Test<
	type::Base::bt_REAL
>;

TEST_F(Real_Type_Declaration_Test, base_kind) {
	EXPECT_EQ(type.base_kind(), type::Base::bt_REAL);
}

TEST_F(Real_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type.is_bool());
}

TEST_F(Real_Type_Declaration_Test, is_numeric) {
	EXPECT_TRUE(type.is_numeric());
}

TEST_F(Real_Type_Declaration_Test, is_integer) {
	EXPECT_FALSE(type.is_integer());
}

using Byte_Type_Declaration_Test = Base_Type_Declaration_Test<
	type::Base::bt_BYTE
>;

TEST_F(Byte_Type_Declaration_Test, base_kind) {
	EXPECT_EQ(type.base_kind(), type::Base::bt_BYTE);
}

TEST_F(Byte_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type.is_bool());
}

TEST_F(Byte_Type_Declaration_Test, is_numeric) {
	EXPECT_TRUE(type.is_numeric());
}

TEST_F(Byte_Type_Declaration_Test, is_integer) {
	EXPECT_TRUE(type.is_integer());
}
