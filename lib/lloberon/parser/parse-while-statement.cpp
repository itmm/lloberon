#include "parser/parser.h"
#include "stmt/while.h"

bool Parser::parse_while_statement(stmt::Statement_Ptr& statement) {
	auto while_statement { std::make_shared<stmt::While>() };
	if (consume(token::keyword_WHILE)) { return true; }
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }
	if (consume(token::keyword_DO)) { return true; }
	stmt::Statement_Sequence statement_sequence;
	if (parse_statement_sequence(statement_sequence)) { return true; }
	while_statement->entries.emplace_back(
		expression, std::move(statement_sequence)
	);
	while (token::is(token::keyword_ELSIF)) {
		advance();
		if (parse_expression(expression)) { return true; }
		if (consume(token::keyword_DO)) { return true; }
		if (parse_statement_sequence(statement_sequence)) { return true; }
		while_statement->entries.emplace_back(
			expression, std::move(statement_sequence)
		);
	}
	if (consume(token::keyword_END)) { return true; }
	statement = while_statement;
	return false;
}