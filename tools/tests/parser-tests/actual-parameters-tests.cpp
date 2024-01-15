#include "parser-tests.h"

using Actual_Parameters_Runner = Parser_Value_Runner<
	sema::Actual_Parameters, &Parser::parse_actual_parameters
>;

TEST(Actual_Parameters_Tests, empty) {
	Context context;
	sema::Actual_Parameters actual_parameters { context };
	Actual_Parameters_Runner test1 { "", actual_parameters, true };
	Actual_Parameters_Runner test2 { "()", actual_parameters };
}

TEST(Actual_Parameters_Tests, simple) {
	Context context;
	sema::Actual_Parameters actual_parameters { context };
	Actual_Parameters_Runner test1 { "(3, 4)", actual_parameters };
}

TEST(Actual_Paramaters_Tests, incomplete) {
	Context context;
	sema::Actual_Parameters actual_parameters { context };
	Actual_Parameters_Runner test1 { "3", actual_parameters, true, true };
	Actual_Parameters_Runner test2 { "(3", actual_parameters, true };
	Actual_Parameters_Runner test3 { "(", actual_parameters, true };
}