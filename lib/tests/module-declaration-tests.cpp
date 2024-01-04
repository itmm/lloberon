#include "gtest/gtest.h"
#include "lloberon/ast/declaration.h"

class Module_Declaration_Test: public testing::Test {
protected:
    lloberon::Module_Declaration decl { llvm::SMLoc { }, "", "" };

    char source[10] { 0 };

    void SetUp() override {
        new (&decl) lloberon::Module_Declaration {
            llvm::SMLoc::getFromPointer(source), "a", "b"
        };
    }
};

TEST_F(Module_Declaration_Test, kind) {
    EXPECT_EQ(decl.kind(), lloberon::Declaration::DK_Module);
}

TEST_F(Module_Declaration_Test, location) {
    EXPECT_EQ(decl.location().getPointer(), source);
}

TEST_F(Module_Declaration_Test, name) {
    EXPECT_STREQ(decl.name().c_str(), "a");
}

TEST_F(Module_Declaration_Test, no_enclosing_decl) {
    EXPECT_EQ(decl.enclosing_declaration(), nullptr);
}

TEST_F(Module_Declaration_Test, class_of) {
    EXPECT_TRUE(lloberon::Module_Declaration::classof(&decl));
}

TEST_F(Module_Declaration_Test, full_name) {
    EXPECT_STREQ(decl.full_name().c_str(), "b");
}
