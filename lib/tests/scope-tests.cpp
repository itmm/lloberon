#include "gtest/gtest.h"
#include "sema/scope.h"
#include "sema/declaration.h"

TEST(Scope_Tests, no_parent) {
    Scope scope;
    EXPECT_EQ(scope.parent(), nullptr);
}

TEST(Scope_Tests, with_parent) {
    Scope parent;
    Scope scope { &parent };
    EXPECT_EQ(scope.parent(), &parent);
}

TEST(Scope_Tests, not_found) {
    Scope scope;
    EXPECT_EQ(scope.lookup("abc"), nullptr);
}

TEST(Scope_Tests, insert) {
    auto decl { new Variable_Declaration(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    ) };
    {
        Scope scope;
        EXPECT_TRUE(scope.insert(decl));
        EXPECT_EQ(scope.lookup("abc"), decl);
    }
    delete decl;
}

TEST(Scope_Tests, not_found_with_parent) {
    Scope parent;
    Scope scope { &parent };
    EXPECT_EQ(scope.lookup("abc"), nullptr);
}

TEST(Scope_Tests, insert_with_parent) {
    auto decl { new Variable_Declaration(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    ) };
    {
        Scope parent;
        Scope scope { &parent };
        EXPECT_TRUE(parent.insert(decl));
        EXPECT_EQ(scope.lookup("abc"), decl);
    }
    delete decl;
}

TEST(Scope_Tests, double_insert) {
    auto first { new Variable_Declaration(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    ) };
    auto second { new Variable_Declaration(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    ) };
    {
        Scope scope;
        EXPECT_TRUE(scope.insert(first));
        EXPECT_FALSE(scope.insert(second));
        EXPECT_EQ(scope.lookup("abc"), first);
    }
    delete second;
    delete first;
}