#include "parser/parser.h"
#include "stmt/while.h"

void Parser::parse_while_statement(stmt::Statement_Ptr& statement) {
	auto while_statement { std::make_shared<stmt::While>() };
	consume(token::keyword_WHILE);
	expr::Expression_Ptr expression;
	parse_expression(expression);
	consume(token::keyword_DO);
	stmt::Statement_Sequence statement_sequence;
	parse_statement_sequence(statement_sequence);
	while_statement->entries.emplace_back(
		expression, std::move(statement_sequence)
	);
	while (token::is(token::keyword_ELSIF)) {
		advance();
		parse_expression(expression);
		consume(token::keyword_DO);
		parse_statement_sequence(statement_sequence);
		while_statement->entries.emplace_back(
			expression, std::move(statement_sequence)
		);
	}
	consume(token::keyword_END);
	statement = while_statement;
}