#include "parser/parser.h"

bool Parser::parse_declaration_sequence(Scope& scope) {
	if (token_.is(token::keyword_CONST)) {
		advance();
		while (token_.is(token::identifier)) {
			if (parse_const_declaration(scope)) { return true; }
			if (consume(token::semicolon)) { return true; }
		}
	}
	if (token_.is(token::keyword_TYPE)) {
		advance();
		while (token_.is(token::identifier)) {
			if (parse_type_declaration(scope)) { return true; }
			if (consume(token::semicolon)) { return true; }
		}
	}
	if (token_.is(token::keyword_VAR)) {
		advance();
		while (token_.is(token::identifier)) {
			if (parse_variable_declaration(scope)) { return true; }
			if (consume(token::semicolon)) { return true; }
		}
	}

	while (token_.is(token::keyword_PROCEDURE)) {
		sema::Procedure_Declaration procedure_declaration { scope };
		if (parse_procedure_declaration(procedure_declaration)) { return true; }
		if (consume(token::semicolon)) { return true; }
	}
	return false;
}