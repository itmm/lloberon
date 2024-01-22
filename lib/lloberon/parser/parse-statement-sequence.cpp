#include "parser/parser.h"

void Parser::parse_statement_sequence(
	stmt::Statement_Sequence& statement_sequence
) {
	statement_sequence.clear();
	stmt::Statement_Ptr statement;
	parse_statement(statement);
	statement_sequence.push_back(statement);
	while (token::is(token::semicolon)) {
		advance();
		parse_statement(statement);
		statement_sequence.push_back(statement);
	}
}