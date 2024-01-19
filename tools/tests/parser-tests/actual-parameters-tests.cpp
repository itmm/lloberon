#include "parser-tests.h"

using Actual_Parameters_Runner = Parser_String_Runner<
	&Parser::parse_actual_parameters
>;

TEST(Actual_Parameters_Tests, empty) {
	Actual_Parameters_Runner test1 { "", true };
	Actual_Parameters_Runner test2 { "()" };
}

TEST(Actual_Parameters_Tests, simple) {
	Actual_Parameters_Runner test1 { "(3, 4)" };
}

TEST(Actual_Paramaters_Tests, incomplete) {
	Actual_Parameters_Runner test1 { "3", true, true };
	Actual_Parameters_Runner test2 { "(3", true };
	Actual_Parameters_Runner test3 { "(", true };
}