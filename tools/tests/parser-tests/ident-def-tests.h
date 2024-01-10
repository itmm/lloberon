#pragma once

#include "sema/ident-def.h"

#include "gtest/gtest.h"

inline void expect_ident_def(
	const sema::Ident_Def& ident_def, const char* name, bool exported
) {
	EXPECT_STREQ(ident_def.ident.c_str(), name);
	if (exported) {
		EXPECT_TRUE(ident_def.exported);
	} else {
		EXPECT_FALSE(ident_def.exported);
	}
}

inline void expect_empty_ident_def(const sema::Ident_Def& ident_def) {
	expect_ident_def(ident_def, "", false);
}