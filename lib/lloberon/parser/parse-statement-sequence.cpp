#include "parser/parser.h"

bool Parser::parse_statement_sequence(
	sema::Statement_Sequence& statement_sequence
) {
	sema::Statement statement { statement_sequence.scope() };
	if (parse_statement(statement)) { return true; }
	statement_sequence.sequence.push_back(statement.statement);
	while (token_.is(token::semicolon)) {
		advance();
		if (parse_statement(statement)) { return true; }
		statement_sequence.sequence.push_back(statement.statement);
	}
	return false;
}