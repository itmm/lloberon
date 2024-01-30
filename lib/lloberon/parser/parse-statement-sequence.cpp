#include "parser/parser.h"

void Parser::parse_statement_sequence(
	stmt::Statement_Sequence& statement_sequence
) {
	statement_sequence.clear();
	statement_sequence.push_back(parse_statement());
	while (token::is(token::semicolon)) {
		advance();
		statement_sequence.push_back(parse_statement());
	}
}