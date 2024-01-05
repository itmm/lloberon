#pragma once

#include "lexer/lexer.h"
#include "llvm/Support/raw_ostream.h"
#include "sema/actual-parameters.h"
#include "sema/array-type.h"
#include "sema/assignment-or-procedure-call.h"
#include "sema/base-type.h"
#include "sema/case.h"
#include "sema/case-list.h"
#include "sema/case-statement.h"
#include "sema/declaration-sequence.h"
#include "sema/designator.h"
#include "sema/expression.h"
#include "sema/expression-list.h"
#include "sema/factor.h"
#include "sema/field-list.h"
#include "sema/field-list-sequence.h"
#include "sema/for-statement.h"
#include "sema/formal-parameter-section.h"
#include "sema/formal-parameters.h"
#include "sema/formal-type.h"
#include "sema/ident-def.h"
#include "sema/if-statement.h"
#include "sema/label.h"
#include "sema/pointer-type.h"
#include "sema/procedure-body.h"
#include "sema/procedure-declaration.h"
#include "sema/procedure-heading.h"
#include "sema/procedure-type.h"
#include "sema/record-type.h"
#include "sema/repeat-statement.h"
#include "sema/simple-expression.h"
#include "sema/scope.h"
#include "sema/statement.h"
#include "sema/statement-sequence.h"
#include "sema/term.h"
#include "sema/type.h"
#include "sema/type-declaration.h"
#include "sema/qual-ident.h"
#include "sema/var-declaration.h"
#include "sema/while-statement.h"

class Parser {
    Lexer &lexer_;
    Token token_ { };

    void error() {
        diag().report(
                token_.location(), diag::err_unexpected,
                token::token_name(token_.kind())
        );
    }

    void advance() { lexer_.next(token_); }

    Base_Diagnostic_Engine& diag() { return lexer_.diag(); }

    [[nodiscard]] bool expect(token::Kind kind) {
        if (!token_.is(kind)) {
            const char* expected = token::punctuator_spelling(kind);
            if (!expected) { expected = token::keyword_spelling(kind); }
            if (!expected) { expected = token::token_name(kind); }

            llvm::StringRef actual(
                token_.location().getPointer(), token_.length()
            );

            diag().report(
                token_.location(), diag::err_expected,
                expected, actual
            );
            return true;
        }
        return false;
    }

    [[nodiscard]] bool consume(token::Kind kind) {
        if (expect(kind)) { return true; }
        advance();
        return false;
    }

public:
    explicit Parser(Lexer &lexer) : lexer_ { lexer } { advance(); }

    [[nodiscard]] bool parse();
    [[nodiscard]] bool parse_simple_expression(lloberon::sema::Simple_Expression& expression);
    [[nodiscard]] bool parse_expression(sema::Expression& expression);
    [[nodiscard]] bool parse_term(lloberon::sema::Term& term);

    [[nodiscard]] bool parse_element();
    [[nodiscard]] bool parse_set();
    [[nodiscard]] bool parse_factor(lloberon::sema::Factor& factor);

    [[nodiscard]] bool parse_import(Scope& scope);
    [[nodiscard]] bool parse_import_list(Scope& scope);
    [[nodiscard]] bool parse_ident_def(lloberon::sema::Ident_Def& ident_def);
    [[nodiscard]] bool parse_const_expression();
    [[nodiscard]] bool parse_const_declaration();
    [[nodiscard]] bool parse_qual_ident(lloberon::sema::Qual_Ident& qual_ident);
    [[nodiscard]] bool parse_length();
    [[nodiscard]] bool parse_array_type(sema::Array_Type& array_type);
    [[nodiscard]] bool parse_base_type(sema::Base_Type& base_type);
    [[nodiscard]] bool parse_ident_list(lloberon::sema::Ident_List& ident_list);
    [[nodiscard]] bool parse_field_list(lloberon::sema::Field_List& field_list);
    [[nodiscard]] bool parse_field_list_sequence(lloberon::sema::Field_List_Sequence& field_list_sequence);
    [[nodiscard]] bool parse_record_type(lloberon::sema::Record_Type& record_type);
    [[nodiscard]] bool parse_pointer_type(lloberon::sema::Pointer_Type& pointer_type);
    [[nodiscard]] bool parse_formal_type(lloberon::sema::Formal_Type& formal_type);
    [[nodiscard]] bool parse_formal_parameter_section(
        lloberon::sema::Formal_Parameter_Section& formal_parameter_section
    );
    [[nodiscard]] bool parse_formal_parameters(lloberon::sema::Formal_Parameters& formal_parameters);
    [[nodiscard]] bool parse_procedure_type(lloberon::sema::Procedure_Type& procedure_type);
    [[nodiscard]] bool parse_type(lloberon::sema::Type& type);
    [[nodiscard]] bool parse_type_declaration(lloberon::sema::Type_Declaration& type_declaration);
    [[nodiscard]] bool parse_variable_declaration(lloberon::sema::Var_Declaration& var_declaration);
    [[nodiscard]] bool parse_procedure_heading(lloberon::sema::Procedure_Heading& procedure_heading);
    [[nodiscard]] bool parse_procedure_body(lloberon::sema::Procedure_Body& procedure_body);
    [[nodiscard]] bool parse_procedure_declaration(
        lloberon::sema::Procedure_Declaration& procedure_declaration
    );
    [[nodiscard]] bool parse_declaration_sequence(
        sema::Declaration_Sequence& declaration_sequence
    );
    [[nodiscard]] bool parse_module(Scope& scope);
    [[nodiscard]] bool parse_expression_list(sema::Expression_List& expression_list);
    [[nodiscard]] bool parse_designator(sema::Designator& designator);
    [[nodiscard]] bool parse_actual_parameters(sema::Actual_Parameters& actual_parameters);
    [[nodiscard]] bool parse_assignment_or_procedure_call(
        sema::Assignment_Or_Procedure_Call& assignment_or_procedure_call
    );
    [[nodiscard]] bool parse_if_statement(lloberon::sema::If_Statement& if_statement);
    [[nodiscard]] bool parse_label(lloberon::sema::Label& label);
    [[nodiscard]] bool parse_label_range();
    [[nodiscard]] bool parse_case_list(sema::Case_List& case_list);
    [[nodiscard]] bool parse_case(sema::Case& case_arg);
    [[nodiscard]] bool parse_case_statement(sema::Case_Statement& case_statement);
    [[nodiscard]] bool parse_while_statement(lloberon::sema::While_Statement& while_statement);
    [[nodiscard]] bool parse_repeat_statement(lloberon::sema::Repeat_Statement& repeat_statement);
    [[nodiscard]] bool parse_for_statement(lloberon::sema::For_Statement& for_statement);
    [[nodiscard]] bool parse_statement(lloberon::sema::Statement& statement);
    [[nodiscard]] bool parse_statement_sequence(lloberon::sema::Statement_Sequence& statement_sequence);

    [[nodiscard]] bool is_eof() { return token_.is(token::eof); }
};