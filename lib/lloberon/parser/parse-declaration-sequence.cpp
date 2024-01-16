#include "parser/parser.h"

bool Parser::parse_declaration_sequence(Context& context) {
	if (token::is(token::keyword_CONST)) {
		advance();
		while (token::is(token::identifier)) {
			if (parse_const_declaration(context)) { return true; }
			if (consume(token::semicolon)) { return true; }
		}
	}
	if (token::is(token::keyword_TYPE)) {
		advance();
		while (token::is(token::identifier)) {
			if (parse_type_declaration(context)) { return true; }
			if (consume(token::semicolon)) { return true; }
		}
	}
	if (token::is(token::keyword_VAR)) {
		advance();
		while (token::is(token::identifier)) {
			if (parse_variable_declaration(context)) { return true; }
			if (consume(token::semicolon)) { return true; }
		}
	}

	while (token::is(token::keyword_PROCEDURE)) {
		if (parse_procedure_declaration(context)) { return true; }
		if (consume(token::semicolon)) { return true; }
	}
	return false;
}