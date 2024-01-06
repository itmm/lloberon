#include "parser-tests.h"
#include "decl/base-type.h"

using Label_Runner = Parser_Value_Runner<
    sema::Label, &Parser::parse_label
>;

TEST(Label_Tests, empty) {
    Scope scope;
    sema::Label label { scope };
    Label_Runner test1 { "", label, true };
}

TEST(Label_Tests, simple) {
    Scope scope;
    sema::Label label { scope };
    Label_Runner test1 { "3", label };

    label.clear();
    Label_Runner test2 { "\"abc\"", label };
}

TEST(Label_Tests, qual_ident) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    auto module { std::make_shared<decl::Module>(
        llvm::SMLoc {}, "X", "X"
    ) };
    module->insert(std::make_shared<decl::Base_Type>(
        "Byte", decl::Base_Type::bt_BYTE
    ));
    scope.insert(module);
    sema::Label label { scope };
    Label_Runner test1 { "INTEGER", label };

    label.clear();
    Label_Runner test2 { "X.Byte", label };
}

TEST(Label_Tests, wrong) {
    Scope scope;
    auto module { std::make_shared<decl::Module>(
        llvm::SMLoc {}, "X", "X"
    ) };
    scope.insert(module);
    sema::Label label { scope };
    Label_Runner test1 { "X.", label, true };

    label.clear();
    Label_Runner test2 { "NIL", label, true, true };
}