#include "parser/parser.h"

void Parser::parse_procedure_body(decl::Procedure& procedure_declaration) {
	parse_declaration_sequence();
	if (token::is(token::keyword_BEGIN)) {
		advance();
		auto statement_sequence { parse_statement_sequence() };
	}
	if (token::is(token::keyword_RETURN)) {
		advance();
		auto expression { parse_expression() };
	}
	consume(token::keyword_END);
}