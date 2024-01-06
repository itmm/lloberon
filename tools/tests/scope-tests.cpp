#include "gtest/gtest.h"
#include "sema/scope.h"
#include "decl/declaration.h"
#include "decl/variable.h"

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
    Scope scope;
    EXPECT_TRUE(scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    )));
    EXPECT_STREQ(scope.lookup("abc")->name().c_str(), "abc");
}

TEST(Scope_Tests, not_found_with_parent) {
    Scope parent;
    Scope scope { &parent };
    EXPECT_EQ(scope.lookup("abc"), nullptr);
}

TEST(Scope_Tests, insert_with_parent) {
    Scope parent;
    Scope scope { &parent };
    EXPECT_TRUE(parent.insert(std::make_shared<decl::Variable>(
            nullptr, llvm::SMLoc { }, "abc", nullptr
    )));
    EXPECT_STREQ(scope.lookup("abc")->name().c_str(), "abc");
}

TEST(Scope_Tests, double_insert) {
    auto first { std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    ) };
    auto second { std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc { }, "abc", nullptr
    ) };
    Scope scope;
    EXPECT_TRUE(scope.insert(first));
    EXPECT_FALSE(scope.insert(second));
    EXPECT_EQ(scope.lookup("abc"), first);
}