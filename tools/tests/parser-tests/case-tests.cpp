#include "parser-tests.h"

using Case_Runner = Parser_Value_Runner<sema::Case, &Parser::parse_case>;

TEST(Case_Tests, empty) {
    Scope scope;
    sema::Case case_arg { scope };
    Case_Runner("", case_arg, true);
}

TEST(Case_Tests, simple) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::Case case_arg { scope };
    Case_Runner test1 { "3..4:", case_arg };

    case_arg.clear();
    Case_Runner test2 { "3..4: a := 3", case_arg };
}

TEST(Case_Tests, wrong) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::Case case_arg { scope };
    Case_Runner test1 { "3 a := 3", case_arg, true, true };

    case_arg.clear();
    Case_Runner test2 { "3",case_arg, true };
}