#include "parser/parser.h"

bool Parser::parse_statement_sequence(
	stmt::Statement_Sequence& statement_sequence
) {
	statement_sequence.clear();
	stmt::Statement_Ptr statement;
	if (parse_statement(statement)) { return true; }
	statement_sequence.push_back(statement);
	while (token::is(token::semicolon)) {
		advance();
		if (parse_statement(statement)) { return true; }
		statement_sequence.push_back(statement);
	}
	return false;
}