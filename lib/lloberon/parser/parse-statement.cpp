#include "parser/parser.h"

void Parser::parse_statement(stmt::Statement_Ptr& statement) {
	if (token::is(token::identifier)) {
		expr::Expression_Ptr expression;
		parse_assignment_or_procedure_call(expression);
	} else if (token::is(token::keyword_IF)) {
		statement = parse_if_statement();
	} else if (token::is(token::keyword_CASE)) {
		statement = parse_case_statement();
	} else if (token::is(token::keyword_WHILE)) {
		parse_while_statement(statement);
	} else if (token::is(token::keyword_REPEAT)) {
		statement = parse_repeat_statement();
	} else if (token::is(token::keyword_FOR)) {
		statement = parse_for_statement();
	}
}
