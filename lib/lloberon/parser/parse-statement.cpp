#include "parser/parser.h"

bool Parser::parse_statement(stmt::Statement_Ptr& statement) {
	if (token::is(token::identifier)) {
		expr::Expression_Ptr expression;
		if (parse_assignment_or_procedure_call(expression)) { return true; }
	} else if (token::is(token::keyword_IF)) {
		if (parse_if_statement(statement)) { return true; }
	} else if (token::is(token::keyword_CASE)) {
		if (parse_case_statement(statement)) { return true; }
	} else if (token::is(token::keyword_WHILE)) {
		if (parse_while_statement(statement)) { return true; }
	} else if (token::is(token::keyword_REPEAT)) {
		if (parse_repeat_statement(statement)) { return true; }
	} else if (token::is(token::keyword_FOR)) {
		if (parse_for_statement(statement)) { return true; }
	}
	return false;
}
