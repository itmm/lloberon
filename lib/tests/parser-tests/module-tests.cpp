#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Module_Runner = Parser_Value_Runner<
    Scope, &Parser::parse_module
>;

TEST(Module_Tests, empty) {
    Scope scope;
    Module_Runner("", scope, true);
}

TEST(Module_Tests, simple) {
    Scope scope;
    Module_Runner("MODULE A; END A.", scope);
}

TEST(Module_Tests, with_imports) {
    Scope scope;
    Module_Runner("MODULE A; IMPORT x := y; END A.", scope);
}

TEST(Module_Tests, with_declarations) {
    Scope scope;
    Module_Runner("MODULE A; CONST B = 3; END A.", scope);
}

TEST(Module_Tests, with_statements) {
    Scope scope;
    scope.insert(new Variable_Declaration {
        nullptr, {}, "EXIT", nullptr
    });
    Module_Runner("MODULE A; BEGIN EXIT(10) END A.", scope);
}

TEST(Module_Tests, with_multiple) {
    Scope scope;
    scope.insert(new Variable_Declaration {
            nullptr, {}, "EXIT", nullptr
    });
    scope.insert(new Variable_Declaration {
            nullptr, {}, "B", nullptr
    });
    Module_Runner("MODULE A; IMPORT x; CONST B = 3; BEGIN EXIT(B) END A.", scope);

    new (&scope) Scope {};
    Module_Runner("MODULE A; IMPORT x; CONST B = 3; END A.", scope);

    new (&scope) Scope {};
    scope.insert(new Variable_Declaration {
            nullptr, {}, "EXIT", nullptr
    });
    Module_Runner("MODULE A; IMPORT x; BEGIN EXIT(10) END A.", scope);

    new (&scope) Scope {};
    scope.insert(new Variable_Declaration {
            nullptr, {}, "EXIT", nullptr
    });
    scope.insert(new Variable_Declaration {
            nullptr, {}, "B", nullptr
    });
    Module_Runner("MODULE A; CONST B = 3; BEGIN EXIT(B) END A.", scope);
}

TEST(Module_Tests, names_dont_match) {
    Scope scope;
    Module_Runner("MODULE A; END B.", scope, true, true);
}

TEST(Module_Tests, no_semicolon) {
    Scope scope;
    Module_Runner("MODULE A END A.", scope, true, true);
}

TEST(Module_Tests, no_period) {
    Scope scope;
    Module_Runner("MODULE A; END A", scope, true);
}

TEST(Module_Tests, no_names) {
    Scope scope;
    Module_Runner("MODULE END.", scope, true, true);
    Module_Runner("MODULE A END.", scope, true, true);
    Module_Runner("MODULE END A.", scope, true, true);
}

TEST(Module_Tests, wrong_order) {
    Scope scope;
    Module_Runner("MODULE A; CONST B = 3; IMPORT x; END A.", scope, true, true);
}

#pragma clang diagnostic pop