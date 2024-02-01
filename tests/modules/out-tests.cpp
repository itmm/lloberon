#include "gtest/gtest.h"
#include "modules/out.h"

class Out_Module_Test : public testing::Test {
public:
	Out_Module_Test() { Init_Module(); }
protected:
	static std::ostringstream out;

	static void add_ch(char ch) { out << ch; }

	void SetUp() override { out = {}; set_output(&add_ch); }

	void TearDown() override { reset_output(); }

	static void expect_str(const char* expected) {
		EXPECT_STREQ(out.str().c_str(), expected);
	}

	static void expect_int(int x, int n, const char* expected) {
		WriteInt(x, n); expect_str(expected);
	}
};

std::ostringstream Out_Module_Test::out;

TEST_F(Out_Module_Test, zero) { expect_int(0, 0, "0"); }
TEST_F(Out_Module_Test, positive) { expect_int(123, 2, "123"); }
TEST_F(Out_Module_Test, negative) { expect_int(-123, 0, "-123"); }
TEST_F(Out_Module_Test, padded_positive) { expect_int(123, 6, "   123"); }
TEST_F(Out_Module_Test, padded_negative) { expect_int(-123, 6, "  -123"); }
TEST_F(Out_Module_Test, max_negative) {
	expect_int(-2147483648, 0, "-2147483648");
}

TEST_F(Out_Module_Test, newline) { WriteLn(); expect_str("\n"); }