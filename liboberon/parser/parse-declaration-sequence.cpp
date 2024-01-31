#include "parser/parser.h"

void Parser::parse_declaration_sequence() {
	if (token::is(token::keyword_CONST)) {
		advance();
		while (token::is(token::identifier)) {
			parse_const_declaration();
			consume(token::semicolon);
		}
	}
	if (token::is(token::keyword_TYPE)) {
		advance();
		while (token::is(token::identifier)) {
			parse_type_declaration();
			consume(token::semicolon);
		}
	}
	if (token::is(token::keyword_VAR)) {
		advance();
		while (token::is(token::identifier)) {
			parse_variable_declaration();
			consume(token::semicolon);
		}
	}

	while (token::is(token::keyword_PROCEDURE)) {
		parse_procedure_declaration();
		consume(token::semicolon);
	}
}