#pragma once

#include "ident-def-tests.h"

inline void expect_empty_ident_list(const sema::Ident_List& list) {
    EXPECT_TRUE(list.empty());
}

inline void expect_ident_list(
    const sema::Ident_List& list, const char *ident_1, bool exported_1
) {
    EXPECT_EQ(list.size(), 1);
    expect_ident_def(list[0], ident_1, exported_1);
}

inline void expect_ident_list(
        const sema::Ident_List& list, const char *ident_1, bool exported_1,
        const char* ident_2, bool exported_2
) {
    EXPECT_EQ(list.size(), 2);
    expect_ident_def(list[0], ident_1, exported_1);
    expect_ident_def(list[1], ident_2, exported_2);
}

inline void expect_ident_list(
    const sema::Ident_List& list, const char *ident_1, bool exported_1,
    const char* ident_2, bool exported_2, const char* ident_3, bool exported_3
) {
    EXPECT_EQ(list.size(), 3);
    expect_ident_def(list[0], ident_1, exported_1);
    expect_ident_def(list[1], ident_2, exported_2);
    expect_ident_def(list[2], ident_3, exported_3);
}
