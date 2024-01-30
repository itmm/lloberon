#include "parser/parser.h"

stmt::Statement_Ptr Parser::parse_statement() {
	if (token::is(token::identifier)) {
		expr::Expression_Ptr expression;
		parse_assignment_or_procedure_call(expression);
		return std::make_shared<stmt::Statement>();
	} else if (token::is(token::keyword_IF)) {
		return parse_if_statement();
	} else if (token::is(token::keyword_CASE)) {
		return parse_case_statement();
	} else if (token::is(token::keyword_WHILE)) {
		stmt::Statement_Ptr statement;
		parse_while_statement(statement);
		return statement;
	} else if (token::is(token::keyword_REPEAT)) {
		return parse_repeat_statement();
	} else if (token::is(token::keyword_FOR)) {
		return parse_for_statement();
	}
	return nullptr;
}
