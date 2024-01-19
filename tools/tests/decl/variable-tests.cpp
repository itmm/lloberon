#include "gtest/gtest.h"
#include "decl/declaration.h"
#include "expr/variable.h"

class Var_Declaration_Test : public testing::Test {
protected:
	expr::Variable decl { nullptr };

	void SetUp() override {
		decl.~Variable();
		new(&decl) expr::Variable { nullptr };
	}
};

TEST_F(Var_Declaration_Test, type) {
	EXPECT_EQ(decl.type, nullptr);
}
