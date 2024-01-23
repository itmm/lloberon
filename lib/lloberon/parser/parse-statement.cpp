#include "parser/parser.h"

void Parser::parse_statement(stmt::Statement_Ptr& statement) {
	if (token::is(token::identifier)) {
		expr::Expression_Ptr expression;
		parse_assignment_or_procedure_call(expression);
	} else if (token::is(token::keyword_IF)) {
		parse_if_statement(statement);
	} else if (token::is(token::keyword_CASE)) {
		statement = parse_case_statement();
	} else if (token::is(token::keyword_WHILE)) {
		parse_while_statement(statement);
	} else if (token::is(token::keyword_REPEAT)) {
		parse_repeat_statement(statement);
	} else if (token::is(token::keyword_FOR)) {
		parse_for_statement(statement);
	}
}
