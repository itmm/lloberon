#include "parser/parser.h"

bool Parser::parse_procedure_body(
	sema::Procedure_Declaration& procedure_declaration
) {
	if (parse_declaration_sequence()) {
		return true;
	}
	if (token::is(token::keyword_BEGIN)) {
		advance();
		stmt::Statement_Sequence statement_sequence;
		if (parse_statement_sequence(statement_sequence)) { return true; }
	}
	if (token::is(token::keyword_RETURN)) {
		advance();
		expr::Expression_Ptr expression;
		if (parse_expression(expression)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	return false;
}