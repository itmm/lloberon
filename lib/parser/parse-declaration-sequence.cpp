#include "parser/parser.h"

bool Parser::parse_declaration_sequence(sema::Declaration_Sequence& declaration_sequence) {
    if (token_.is(token::keyword_CONST)) {
        advance();
        while (token_.is(token::identifier)) {
            if (parse_const_declaration()) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }
    if (token_.is(token::keyword_TYPE)) {
        advance();
        while (token_.is(token::identifier)) {
            sema::Type_Declaration type_declaration { declaration_sequence.scope() };
            if (parse_type_declaration(type_declaration)) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }
    if (token_.is(token::keyword_VAR)) {
        advance();
        while (token_.is(token::identifier)) {
            sema::Var_Declaration var_declaration { declaration_sequence.scope() };
            if (parse_variable_declaration(var_declaration)) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }

    while (token_.is(token::keyword_PROCEDURE)) {
        sema::Procedure_Declaration procedure_declaration { declaration_sequence.scope() };
        if (parse_procedure_declaration(procedure_declaration)) { return true; }
        if (consume(token::semicolon)) { return true; }
    }
    return false;
}