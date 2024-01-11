#include "type/type.h"
#include "gtest/gtest.h"

class Base_Type_Declaration_Test : public testing::Test {
public:
	explicit Base_Type_Declaration_Test(std::shared_ptr<type::Type> base) :
		type { std::move(base) } { }

protected:
	std::shared_ptr<type::Type> type;
};

class Boolean_Type_Declaration_Test : public Base_Type_Declaration_Test {
	public:
		Boolean_Type_Declaration_Test():
			Base_Type_Declaration_Test { type::Type::base_boolean } { }
};

TEST_F(Boolean_Type_Declaration_Test, is_bool) {
	EXPECT_TRUE(type->is_bool());
}

TEST_F(Boolean_Type_Declaration_Test, is_numeric) {
	EXPECT_FALSE(type->is_numeric());
}

TEST_F(Boolean_Type_Declaration_Test, is_integer) {
	EXPECT_FALSE(type->is_integer());
}

class Char_Type_Declaration_Test : public Base_Type_Declaration_Test {
public:
	Char_Type_Declaration_Test():
		Base_Type_Declaration_Test { type::Type::base_char } { }
};

TEST_F(Char_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type->is_bool());
}

TEST_F(Char_Type_Declaration_Test, is_numeric) {
	EXPECT_FALSE(type->is_numeric());
}

TEST_F(Char_Type_Declaration_Test, is_integer) {
	EXPECT_FALSE(type->is_integer());
}

class Integer_Type_Declaration_Test : public Base_Type_Declaration_Test {
public:
	Integer_Type_Declaration_Test():
		Base_Type_Declaration_Test { type::Type::base_integer } { }
};

TEST_F(Integer_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type->is_bool());
}

TEST_F(Integer_Type_Declaration_Test, is_numeric) {
	EXPECT_TRUE(type->is_numeric());
}

TEST_F(Integer_Type_Declaration_Test, is_integer) {
	EXPECT_TRUE(type->is_integer());
}

class Real_Type_Declaration_Test : public Base_Type_Declaration_Test {
public:
	Real_Type_Declaration_Test():
		Base_Type_Declaration_Test { type::Type::base_real } { }
};

TEST_F(Real_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type->is_bool());
}

TEST_F(Real_Type_Declaration_Test, is_numeric) {
	EXPECT_TRUE(type->is_numeric());
}

TEST_F(Real_Type_Declaration_Test, is_integer) {
	EXPECT_FALSE(type->is_integer());
}

class Byte_Type_Declaration_Test : public Base_Type_Declaration_Test {
public:
	Byte_Type_Declaration_Test():
		Base_Type_Declaration_Test { type::Type::base_byte } { }
};

TEST_F(Byte_Type_Declaration_Test, is_bool) {
	EXPECT_FALSE(type->is_bool());
}

TEST_F(Byte_Type_Declaration_Test, is_numeric) {
	EXPECT_TRUE(type->is_numeric());
}

TEST_F(Byte_Type_Declaration_Test, is_integer) {
	EXPECT_TRUE(type->is_integer());
}
