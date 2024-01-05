#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Designator_Runner = Parser_Value_Runner<
    lloberon::sema::Designator, &lloberon::Parser::parse_designator
>;

TEST(Designator_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Designator designator { scope };
    Designator_Runner("", designator, true);
}

TEST(Designator_Tests, simple) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    lloberon::sema::Designator designator { scope };
    Designator_Runner("a", designator);

    designator.clear();
    Designator_Runner("a.b", designator);

    designator.clear();
    Designator_Runner("a.b.c", designator);

    designator.clear();
    Designator_Runner("a.b[2, 3]", designator);

    designator.clear();
    Designator_Runner("a.b^", designator);
}

TEST(Designator_Tests, combined) {
    lloberon::Scope scope;
    lloberon::sema::Designator designator { scope };
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    Designator_Runner("a.b^[3].c^", designator);
}

TEST(Designator_Tests, incomplete) {
    lloberon::Scope scope;
    lloberon::sema::Designator designator { scope };
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    Designator_Runner("a[3,", designator, true);

    designator.clear();
    Designator_Runner("a[3", designator, true);

    designator.clear();
    Designator_Runner("a[3,]", designator, true);

    designator.clear();
    Designator_Runner("a[]", designator, true);

    designator.clear();
    Designator_Runner("a.b.", designator, true);

    designator.clear();
    Designator_Runner("a.b.[", designator, true, true);

    designator.clear();
    Designator_Runner("a.b.^", designator, true, true);

    designator.clear();
    Designator_Runner("a.", designator, true);

    designator.clear();
    Designator_Runner("a.[", designator, true, true);

    designator.clear();
    Designator_Runner("a.^", designator, true, true);
}

#pragma clang diagnostic pop