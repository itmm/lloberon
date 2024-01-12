#pragma once

#include "gtest/gtest.h"
#include "expr/const.h"
#include "expr/expression.h"

inline void expect_int_value(
	const std::shared_ptr<expr::Expression>& expression, int expected
) {
	auto const_expr { std::dynamic_pointer_cast<expr::Const>(expression) };
	EXPECT_NE(const_expr, nullptr);
	if (const_expr) {
		EXPECT_TRUE(const_expr->is_int());
		if (const_expr->is_int()) {
			EXPECT_EQ(const_expr->int_value(), expected);
		}
	}
}

inline void expect_real_value(
	const std::shared_ptr<expr::Expression>& expression, double expected
) {
	auto const_expr { std::dynamic_pointer_cast<expr::Const>(expression) };
	EXPECT_NE(const_expr, nullptr);
	if (const_expr) {
		EXPECT_TRUE(const_expr->is_real());
		if (const_expr->is_real()) {
			EXPECT_EQ(const_expr->real_value(), expected);
		}
	}
}

inline void expect_bool_value(
	const std::shared_ptr<expr::Expression>& expression, bool expected
) {
	auto const_expr { std::dynamic_pointer_cast<expr::Const>(expression) };
	EXPECT_NE(const_expr, nullptr);
	if (const_expr) {
		EXPECT_TRUE(const_expr->is_bool());
		if (const_expr->is_bool()) {
			bool got { const_expr->bool_value() };
			if (expected) { EXPECT_TRUE(got); } else { EXPECT_FALSE(got); }
		}
	}
}

