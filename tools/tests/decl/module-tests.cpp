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
