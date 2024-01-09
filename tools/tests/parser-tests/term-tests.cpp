#include "parser-tests.h"
#include "decl/variable.h"

using Term_Runner = Parser_Value_Runner<sema::Term, &Parser::parse_term>;

TEST(Term_Tests, empty) {
    Scope scope;
    sema::Term term { scope };
    Term_Runner test1 { "", term, true };
}

TEST(Term_Tests, single) {
    Scope scope;
    sema::Term term { scope };
    Term_Runner test1 { "3", term };
}

TEST(Term_Tests, simple) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("b", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Term term { scope };
    Term_Runner test1 { "a * b", term };

    term.clear();
    Term_Runner test2 { "a / b", term };

    term.clear();
    Term_Runner test3 { "a DIV b", term };

    term.clear();
    Term_Runner test4 { "a MOD b", term };

    term.clear();
    Term_Runner test5 { "a & b", term };
}

TEST(Term_Tests, multiple) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("b", std::make_shared<decl::Variable>(
        nullptr
    ));
    scope.insert("c", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Term term { scope };
    Term_Runner test1 { "a * b * c", term };

    term.clear();
    Term_Runner test2 { "a / 2 DIV b", term };
}

TEST(Term_Tests, incomplete) {
    Scope scope;
    scope.insert("a", std::make_shared<decl::Variable>(
        nullptr
    ));
    sema::Term term { scope };
    Term_Runner test1 { "a / 2 DIV", term, true };

    term.clear();
    Term_Runner test2 { "a /", term, true };
}