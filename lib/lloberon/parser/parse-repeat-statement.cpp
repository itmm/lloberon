#include "parser/parser.h"
#include "stmt/repeat.h"

bool Parser::parse_repeat_statement(stmt::Statement_Ptr& statement) {
	auto repeat_statement { std::make_shared<stmt::Repeat>() };
	if (consume(token::keyword_REPEAT)) { return true; }
	if (parse_statement_sequence(repeat_statement->statements)) { return true; }
	if (consume(token::keyword_UNTIL)) { return true; }
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }
	repeat_statement->condition = expression;
	statement = repeat_statement;
	return false;
}