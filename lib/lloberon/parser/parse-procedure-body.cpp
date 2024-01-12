#include "parser/parser.h"

bool Parser::parse_procedure_body(
	sema::Procedure_Declaration& procedure_declaration
) {
	auto& scope { procedure_declaration.scope() };
	if (parse_declaration_sequence(scope)) { return true; }
	if (token_.is(token::keyword_BEGIN)) {
		advance();
		sema::Statement_Sequence statement_sequence { scope };
		if (parse_statement_sequence(statement_sequence)) { return true; }
	}
	if (token_.is(token::keyword_RETURN)) {
		advance();
		sema::Expression expression { scope };
		if (parse_expression(expression)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	return false;
}