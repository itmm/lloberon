#pragma once

#include "lloberon/lexer/lexer.h"
#include "llvm/Support/raw_ostream.h"

namespace lloberon {
    class Parser {
        Lexer &lexer_;
        Token token_ { };

        void error() {
            llvm::errs() << "Unexpected: " << token::token_name(token_.kind()) << "\n";
        }

        void advance() { lexer_.next(token_); }

        Diagnostics_Engine& diag() { return lexer_.diag(); }

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

        [[nodiscard]] bool parse_simple_expression();
        [[nodiscard]] bool parse_expression();
        [[nodiscard]] bool parse_term();

        [[nodiscard]] bool parse_element();
        [[nodiscard]] bool parse_set();
        [[nodiscard]] bool parse_factor();

        [[nodiscard]] bool parse_import();
        [[nodiscard]] bool parse_import_list();
        [[nodiscard]] bool parse_identdef();
        [[nodiscard]] bool parse_const_expression();
        [[nodiscard]] bool parse_const_declaration();
        [[nodiscard]] bool parse_qualident();
        [[nodiscard]] bool parse_length();
        [[nodiscard]] bool parse_array_type();
        [[nodiscard]] bool parse_base_type();
        [[nodiscard]] bool parse_identlist();
        [[nodiscard]] bool parse_field_list();
        [[nodiscard]] bool parse_field_list_sequence();
        [[nodiscard]] bool parse_record_type();
        [[nodiscard]] bool parse_pointer_type();
        [[nodiscard]] bool parse_formal_type();
        [[nodiscard]] bool parse_formal_parameter_section();
        [[nodiscard]] bool parse_formal_parameters();
        [[nodiscard]] bool parse_procedure_type();
        [[nodiscard]] bool parse_type();
        [[nodiscard]] bool parse_type_declaration();
        [[nodiscard]] bool parse_variable_declaration();
        [[nodiscard]] bool parse_procedure_heading();
        [[nodiscard]] bool parse_procedure_body();
        [[nodiscard]] bool parse_procedure_declaration();
        [[nodiscard]] bool parse_declaration_sequence();
        [[nodiscard]] bool parse_module();
        [[nodiscard]] bool parse_expression_list();
        [[nodiscard]] bool parse_designator();
        [[nodiscard]] bool parse_actual_parameters();
        [[nodiscard]] bool parse_assignment_or_procedure_call();
        [[nodiscard]] bool parse_if_statement();
        [[nodiscard]] bool parse_label();
        [[nodiscard]] bool parse_label_range();
        [[nodiscard]] bool parse_case_list();
        [[nodiscard]] bool parse_case();
        [[nodiscard]] bool parse_case_statement();
        [[nodiscard]] bool parse_while_statement();
        [[nodiscard]] bool parse_repeat_statement();
        [[nodiscard]] bool parse_for_statement();
        [[nodiscard]] bool parse_statement();
        [[nodiscard]] bool parse_statement_sequence();

    public:
        explicit Parser(Lexer &lexer) : lexer_ { lexer } { advance(); }

        [[nodiscard]] bool parse();
    };
}