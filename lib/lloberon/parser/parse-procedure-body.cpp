#include "parser/parser.h"

void Parser::parse_procedure_body(
	sema::Procedure_Declaration& procedure_declaration
) {
	parse_declaration_sequence();
	if (token::is(token::keyword_BEGIN)) {
		advance();
		stmt::Statement_Sequence statement_sequence;
		parse_statement_sequence(statement_sequence);
	}
	if (token::is(token::keyword_RETURN)) {
		advance();
		expr::Expression_Ptr expression { parse_expression() };
	}
	consume(token::keyword_END);
}