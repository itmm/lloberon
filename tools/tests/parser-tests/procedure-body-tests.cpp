#include "parser-tests.h"

using Procedure_Body_Runner = Parser_Value_Runner<
    sema::Procedure_Body, &Parser::parse_procedure_body
>;

TEST(Procedure_Body_Tests, empty) {
    Scope scope;
    sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner test1 { "", procedure_body, true };
}

TEST(Procedure_Body_Tests, simple) {
    Scope scope;
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner test1 { "END", procedure_body };

    procedure_body.clear();
    Procedure_Body_Runner test2 { "RETURN 42 END", procedure_body };

    procedure_body.clear();
    Procedure_Body_Runner test3 { "BEGIN RETURN 42 END", procedure_body };

    procedure_body.clear();
    Procedure_Body_Runner test4 { "BEGIN a := 42; RETURN a END", procedure_body };
}

TEST(Procedure_Body_Tests, with_declaration) {
    Scope scope;
    decl::Base_Type::register_base_types(scope);
    scope.insert(std::make_shared<decl::Variable>(
        nullptr, llvm::SMLoc {}, "a", nullptr
    ));
    sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner test1 { "VAR a: INTEGER; BEGIN a := 42 END", procedure_body };

    procedure_body.clear();
    Procedure_Body_Runner test2 { "CONST a = 42; RETURN a END", procedure_body };
}

TEST(Procedure_Body_Tests, invalid) {
    Scope scope;
    sema::Procedure_Body procedure_body { scope };
    Procedure_Body_Runner test1 { "RETURN END", procedure_body, true };
}