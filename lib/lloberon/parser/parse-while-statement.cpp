#include "parser/parser.h"
#include "stmt/while.h"

bool Parser::parse_while_statement(sema::Statement& statement) {
	auto while_statement { std::make_shared<stmt::While>() };
	if (consume(token::keyword_WHILE)) { return true; }
	sema::Expression expression { statement.context };
	if (parse_expression(expression)) { return true; }
	if (consume(token::keyword_DO)) { return true; }
	sema::Statement_Sequence statement_sequence { statement.context };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	while_statement->entries.emplace_back(
		expression.expression, std::move(statement_sequence.sequence)
	);
	while (token_.is(token::keyword_ELSIF)) {
		advance();
		if (parse_expression(expression)) { return true; }
		if (consume(token::keyword_DO)) { return true; }
		if (parse_statement_sequence(statement_sequence)) { return true; }
		while_statement->entries.emplace_back(
			expression.expression, std::move(statement_sequence.sequence)
		);
	}
	if (consume(token::keyword_END)) { return true; }
	statement.statement = while_statement;
	return false;
}