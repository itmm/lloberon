#include "parser-tests.h"

using Set_Runner = Parser_String_Runner<&Parser::parse_set>;

TEST(Set_Tests, empty) {
	Set_Runner test1 { "", true };
	Set_Runner test2 { "{}" };
}

TEST(Set_Tests, simple) {
	Set_Runner test1 { "{1}" };
	Set_Runner test2 { "{1, 2, 3}" };
}

TEST(Set_Tests, ranges) {
	Set_Runner test1 { "{1..2}" };
	Set_Runner test2 { "{1..2, 4..6}" };
}

TEST(Set_Tests, incomplete) {
	Set_Runner test1 { "{1..3", true };
	Set_Runner test2 { "{1..}", true, true };
	Set_Runner test3 { "{1,}", true, true };
	Set_Runner test4 { "{1,,", true, true };
}