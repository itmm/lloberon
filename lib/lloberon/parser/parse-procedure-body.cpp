#include "parser/parser.h"

bool Parser::parse_procedure_body(
	sema::Procedure_Declaration& procedure_declaration
) {
	if (parse_declaration_sequence(procedure_declaration.context)) {
		return true;
	}
	if (token_.is(token::keyword_BEGIN)) {
		advance();
		sema::Statement_Sequence statement_sequence {
			procedure_declaration.context
		};
		if (parse_statement_sequence(statement_sequence)) { return true; }
	}
	if (token_.is(token::keyword_RETURN)) {
		advance();
		sema::Expression expression { procedure_declaration.context };
		if (parse_expression(expression)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	return false;
}