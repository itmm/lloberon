#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Label_Runner = Parser_Value_Runner<
    lloberon::sema::Label, &lloberon::Parser::parse_label
>;

TEST(Label_Tests, empty) {
    lloberon::Scope scope;
    lloberon::sema::Label label { scope };
    Label_Runner("", label, true);
}

TEST(Label_Tests, simple) {
    lloberon::Scope scope;
    lloberon::sema::Label label { scope };
    Label_Runner("3", label);

    label.clear();
    Label_Runner("\"abc\"", label);
}

TEST(Label_Tests, qual_ident) {
    lloberon::Scope scope;
    scope.insert(new lloberon::Base_Type_Declaration {
        "INTEGER", lloberon::Base_Type_Declaration::bt_INTEGER
    });
    auto module { new lloberon::Module_Declaration {
        {}, "X", "X"
    } };
    module->insert(new lloberon::Base_Type_Declaration {
        "Byte", lloberon::Base_Type_Declaration::bt_BYTE
    });
    scope.insert(module);
    lloberon::sema::Label label { scope };
    Label_Runner("INTEGER", label);

    label.clear();
    Label_Runner("X.Byte", label);
}

TEST(Label_Tests, wrong) {
    lloberon::Scope scope;
    auto module { new lloberon::Module_Declaration {
            {}, "X", "X"
    } };
    scope.insert(module);
    lloberon::sema::Label label { scope };
    Label_Runner("X.", label, true);

    label.clear();
    Label_Runner("NIL", label, true, true);
}

#pragma clang diagnostic pop