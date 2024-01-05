#include "parser-tests.h"

using Actual_Parameters_Runner = Parser_Value_Runner<
    sema::Actual_Parameters, &Parser::parse_actual_parameters
>;

TEST(Actual_Parameters_Tests, empty) {
    Scope scope;
    sema::Actual_Parameters actual_parameters { scope };
    Actual_Parameters_Runner test1 { "", actual_parameters, true };

    actual_parameters.clear();
    Actual_Parameters_Runner test2 { "()", actual_parameters };
}

TEST(Actual_Parameters_Tests, simple) {
    Scope scope;
    sema::Actual_Parameters actual_parameters { scope };
    Actual_Parameters_Runner test1 { "(3, 4)", actual_parameters };
}

TEST(Actual_Paramaters_Tests, incomplete) {
    Scope scope;
    sema::Actual_Parameters actual_parameters { scope };
    Actual_Parameters_Runner test1 { "3", actual_parameters, true, true };

    actual_parameters.clear();
    Actual_Parameters_Runner test2 { "(3", actual_parameters, true };

    actual_parameters.clear();
    Actual_Parameters_Runner test3 { "(", actual_parameters, true };
}