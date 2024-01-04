#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_declaration_sequence() {
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
            Scope scope;
            sema::Type_Declaration type_declaration { scope };
            if (parse_type_declaration(type_declaration)) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }
    if (token_.is(token::keyword_VAR)) {
        advance();
        while (token_.is(token::identifier)) {
            Scope scope;
            sema::Var_Declaration var_declaration { scope };
            if (parse_variable_declaration(var_declaration)) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }

    while (token_.is(token::keyword_PROCEDURE)) {
        if (parse_procedure_declaration()) { return true; }
        if (consume(token::semicolon)) { return true; }
    }
    return false;
}