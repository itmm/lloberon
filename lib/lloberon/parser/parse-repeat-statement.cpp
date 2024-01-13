#include "parser/parser.h"
#include "stmt/repeat.h"

bool Parser::parse_repeat_statement(sema::Statement& statement) {
	auto& scope { statement.scope() };
	auto repeat_statement { std::make_shared<stmt::Repeat>() };
	if (consume(token::keyword_REPEAT)) { return true; }
	sema::Statement_Sequence statement_sequence { scope };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	repeat_statement->statements = std::move(statement_sequence.sequence);
	if (consume(token::keyword_UNTIL)) { return true; }
	sema::Expression expression { scope };
	if (parse_expression(expression)) { return true; }
	repeat_statement->condition = expression.expression;
	statement.statement = repeat_statement;
	return false;
}