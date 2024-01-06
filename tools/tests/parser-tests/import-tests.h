#pragma once

#include "gtest/gtest.h"

#include "llvm/Support/Casting.h"

#include "decl/declaration.h"
#include "sema/scope.h"

inline void expect_no_modules(Scope& scope) {
    EXPECT_TRUE(scope.empty());
}

inline void expect_module(Scope& scope, const char* name, const char* full_name) {
    auto got = llvm::dyn_cast<decl::Module>(
            &*scope.lookup(name)
    );
    EXPECT_TRUE(got != nullptr);
    EXPECT_STREQ(got->name().c_str(), name);
    EXPECT_STREQ(got->full_name().c_str(), full_name);
}