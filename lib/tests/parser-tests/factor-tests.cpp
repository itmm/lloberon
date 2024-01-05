#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Factor_Runner = Parser_Value_Runner<
    lloberon::sema::Factor, &lloberon::Parser::parse_factor
>;

TEST(Factor_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Factor factor { scope };
    Factor_Runner("", factor, true);
}

TEST(Factor_Tests, literals) {
    lloberon::Scope scope;
    lloberon::sema::Factor factor { scope };
    Factor_Runner("3", factor);
    factor.clear();
    Factor_Runner("3.241", factor);
    factor.clear();
    Factor_Runner("\"abc\"", factor);
    factor.clear();
    Factor_Runner("NIL", factor);
    factor.clear();
    Factor_Runner("TRUE", factor);
    factor.clear();
    Factor_Runner("FALSE", factor);
}

TEST(Factor_Tests, set) {
    lloberon::Scope scope;
    lloberon::sema::Factor factor { scope };
    Factor_Runner("{3..5}", factor);
}

TEST(Factor_Tests, grouped) {
    lloberon::Scope scope;
    lloberon::sema::Factor factor { scope };
    Factor_Runner("(3 + 4)", factor);
}

TEST(Factor_Tests, ident) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    lloberon::sema::Factor factor { scope };
    Factor_Runner("a", factor);
    factor.clear();
    Factor_Runner("a(3, TRUE)", factor);
    factor.clear();
    Factor_Runner("a[3](TRUE)", factor);
}

TEST(Factor_Tests, incomplete) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    lloberon::sema::Factor factor { scope };
    Factor_Runner("a(3,TRUE", factor, true);
    factor.clear();
    Factor_Runner("a(3,", factor, true);
    factor.clear();
    Factor_Runner("a(3", factor, true);
    factor.clear();
    Factor_Runner("a(", factor, true);
}

#pragma clang diagnostic pop