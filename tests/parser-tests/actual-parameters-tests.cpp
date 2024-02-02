#include "parser-tests.h"
#include "expr/call.h"

using Actual_Parameters_Runner = Parser_Arg_Void_Runner<
	expr::Call, &Parser::parse_actual_parameters
>;

TEST(Actual_Parameters_Tests, empty) {
	expr::Call call { nullptr };
	Actual_Parameters_Runner test1 { "", call, true };
	Actual_Parameters_Runner test2 { "()", call };
}

TEST(Actual_Parameters_Tests, simple) {
	expr::Call call { nullptr };
	Actual_Parameters_Runner test1 { "(3, 4)", call };
}

TEST(Actual_Paramaters_Tests, incomplete) {
	expr::Call call { nullptr };
	Actual_Parameters_Runner test1 { "3", call, true, true };
	Actual_Parameters_Runner test2 { "(3", call, true };
	Actual_Parameters_Runner test3 { "(", call, true };
}