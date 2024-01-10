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
	auto var { std::make_shared<decl::Variable>(
		nullptr
	) };
	EXPECT_TRUE(scope.insert("abc", var));
	EXPECT_EQ(scope.lookup("abc"), var);
}

TEST(Scope_Tests, not_found_with_parent) {
	Scope parent;
	Scope scope { &parent };
	EXPECT_EQ(scope.lookup("abc"), nullptr);
}

TEST(Scope_Tests, insert_with_parent) {
	Scope parent;
	Scope scope { &parent };
	auto var { std::make_shared<decl::Variable>(
		nullptr
	) };
	EXPECT_TRUE(parent.insert("abc", var));
	EXPECT_EQ(scope.lookup("abc"), var);
}

TEST(Scope_Tests, double_insert) {
	auto first { std::make_shared<decl::Variable>(
		nullptr
	) };
	auto second { std::make_shared<decl::Variable>(
		nullptr
	) };
	Scope scope;
	EXPECT_TRUE(scope.insert("abc", first));
	EXPECT_FALSE(scope.insert("abc", second));
	EXPECT_EQ(scope.lookup("abc"), first);
}