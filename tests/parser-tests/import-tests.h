#pragma once

#include "gtest/gtest.h"

#include "llvm/Support/Casting.h"

#include "decl/declaration.h"
#include "decl/module.h"
#include "sema/scope.h"

inline void expect_no_modules(Scope& scope) {
    EXPECT_TRUE(scope.empty());
}

inline void expect_module(Scope& scope, const char* name, const char* full_name) {
    auto got = std::dynamic_pointer_cast<decl::Module>(
        scope.lookup(name)
    );
    EXPECT_TRUE(got != nullptr);
    EXPECT_STREQ(got->name().c_str(), full_name);
}