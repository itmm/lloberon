#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Term_Runner = Parser_Value_Runner<sema::Term, &Parser::parse_term>;

TEST(Term_Tests, empty) {
    Scope scope;
    sema::Term term { scope };
    Term_Runner("", term, true);
}

TEST(Term_Tests, single) {
    Scope scope;
    sema::Term term { scope };
    Term_Runner("3", term);
}

TEST(Term_Tests, simple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
        nullptr, {}, "b", nullptr
    });
    sema::Term term { scope };
    Term_Runner("a * b", term);

    term.clear();
    Term_Runner("a / b", term);

    term.clear();
    Term_Runner("a DIV b", term);

    term.clear();
    Term_Runner("a MOD b", term);

    term.clear();
    Term_Runner("a & b", term);
}

TEST(Term_Tests, multiple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "a", nullptr
    });
    scope.insert(new Variable_Declaration {
            nullptr, {}, "b", nullptr
    });
    scope.insert(new Variable_Declaration {
            nullptr, {}, "c", nullptr
    });
    sema::Term term { scope };
    Term_Runner("a * b * c", term);

    term.clear();
    Term_Runner("a / 2 DIV b", term);
}

TEST(Term_Tests, incomplete) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "a", nullptr
    });
    sema::Term term { scope };
    Term_Runner("a / 2 DIV", term, true);

    term.clear();
    Term_Runner("a /", term, true);
}

#pragma clang diagnostic pop