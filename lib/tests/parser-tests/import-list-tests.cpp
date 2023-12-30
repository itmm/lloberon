#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Import_List_Runner = Parser_String_Runner<&lloberon::Parser::parse_import_list>;

TEST(Import_List_Tests, empty) {
    Import_List_Runner("", true);
}

TEST(Import_List_Tests, simple) {
    Import_List_Runner("IMPORT a;");
    Import_List_Runner("IMPORT a, b;");
    Import_List_Runner("IMPORT a := b, c;");
    Import_List_Runner("IMPORT a, b := c;");
    Import_List_Runner("IMPORT a := b, c := d;");
}

TEST(Import_List_Tests, missing) {
    Import_List_Runner("IMPORT", true);
    Import_List_Runner("IMPORT a", true);
    Import_List_Runner("IMPORT a,", true);
    Import_List_Runner("IMPORT a, b", true);
    Import_List_Runner("IMPORT a :=", true);
    Import_List_Runner("IMPORT a := b", true);
}

#pragma clang diagnostic pop