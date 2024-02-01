#include "gtest/gtest.h"
#include "decl/module.h"

class Module_Declaration_Test : public testing::Test {
protected:
	decl::Module decl { "" };

	void SetUp() override {
		decl.~Module();
		new(&decl) decl::Module { "b" };
	}
};

TEST_F(Module_Declaration_Test, full_name) {
	EXPECT_STREQ(decl.name().c_str(), "b");
}

void expect_module(const char* name, const decl::Module_Ptr& expected) {
	auto got { decl::Module::get_module(name) };
	EXPECT_NE(got, nullptr);
	if (got) {
		EXPECT_EQ(got, expected);
		EXPECT_STREQ(got->name().c_str(), name);
	}
}

TEST_F(Module_Declaration_Test, has_SYSTEM) {
	expect_module("SYSTEM", decl::Module::system_module);
}

TEST_F(Module_Declaration_Test, has_Out) {
	expect_module("Out", decl::Module::out_module);
}