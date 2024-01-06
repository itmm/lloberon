#include "parser-tests.h"
#include "decl/variable.h"

using Designator_Runner = Parser_Value_Runner<
    sema::Designator, &Parser::parse_designator
>;

TEST(Designator_Tests, empty) {
    Scope scope;
    sema::Designator designator { scope };
    Designator_Runner test1 { "", designator, true };
}

TEST(Designator_Tests, simple) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::Designator designator { scope };
    Designator_Runner test1 { "a", designator };

    designator.clear();
    Designator_Runner test2 { "a.b", designator };

    designator.clear();
    Designator_Runner test3 { "a.b.c", designator };

    designator.clear();
    Designator_Runner test4 { "a.b[2, 3]", designator };

    designator.clear();
    Designator_Runner test5 { "a.b^", designator };
}

TEST(Designator_Tests, combined) {
    Scope scope;
    sema::Designator designator { scope };
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    Designator_Runner test1 { "a.b^[3].c^", designator };
}

TEST(Designator_Tests, incomplete) {
    Scope scope;
    sema::Designator designator { scope };
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    Designator_Runner test1 { "a[3,", designator, true };

    designator.clear();
    Designator_Runner test2 { "a[3", designator, true };

    designator.clear();
    Designator_Runner test3 { "a[3,]", designator, true };

    designator.clear();
    Designator_Runner test4 { "a[]", designator, true };

    designator.clear();
    Designator_Runner test5 { "a.b.", designator, true };

    designator.clear();
    Designator_Runner test6 { "a.b.[", designator, true, true };

    designator.clear();
    Designator_Runner test7 { "a.b.^", designator, true, true };

    designator.clear();
    Designator_Runner test8 { "a.", designator, true };

    designator.clear();
    Designator_Runner test9 { "a.[", designator, true, true };

    designator.clear();
    Designator_Runner test10 { "a.^", designator, true, true };
}