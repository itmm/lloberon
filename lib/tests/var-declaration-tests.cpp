#include "gtest/gtest.h"
#include "lloberon/sema/declaration.h"

class Var_Declaration_Test: public testing::Test {
protected:
    lloberon::Variable_Declaration decl {
        nullptr, llvm::SMLoc { }, "", nullptr
    };

    char source[10] { 0 };

    void SetUp() override {
        new (&decl) lloberon::Variable_Declaration {
            nullptr, llvm::SMLoc::getFromPointer(source),
            "abc", nullptr
        };
    }
};

TEST_F(Var_Declaration_Test, kind) {
    EXPECT_EQ(decl.kind(), lloberon::Declaration::DK_Var);
}

TEST_F(Var_Declaration_Test, location) {
    EXPECT_EQ(decl.location().getPointer(), source);
}

TEST_F(Var_Declaration_Test, name) {
    EXPECT_STREQ(decl.name().c_str(), "abc");
}

TEST_F(Var_Declaration_Test, no_enclosing_decl) {
    EXPECT_EQ(decl.enclosing_declaration(), nullptr);
}

TEST_F(Var_Declaration_Test, class_of) {
    EXPECT_TRUE(lloberon::Variable_Declaration::classof(&decl));
}

TEST_F(Var_Declaration_Test, type) {
    EXPECT_EQ(decl.type(), nullptr);
}
