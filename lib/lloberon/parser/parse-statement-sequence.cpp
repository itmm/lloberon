#include "parser/parser.h"

stmt::Statement_Sequence Parser::parse_statement_sequence() {
	stmt::Statement_Sequence statement_sequence;
	statement_sequence.push_back(parse_statement());
	while (token::is(token::semicolon)) {
		advance();
		statement_sequence.push_back(parse_statement());
	}
	return statement_sequence;
}