#include "parser/parser.h"
#include "stmt/if.h"

bool Parser::parse_if_statement(stmt::Statement_Ptr& statement) {
	auto if_statement { std::make_shared<stmt::If>() };
	if (consume(token::keyword_IF)) { return true; }
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }
	if (consume(token::keyword_THEN)) { return true; }
	stmt::Statement_Sequence statement_sequence;
	if (parse_statement_sequence(statement_sequence)) { return true; }
	if_statement->entries.emplace_back(
		expression, std::move(statement_sequence)
	);
	while (token::is(token::keyword_ELSIF)) {
		advance();
		expr::Expression_Ptr sub_expression;
		if (parse_expression(sub_expression)) { return true; }
		if (consume(token::keyword_THEN)) { return true; }
		stmt::Statement_Sequence sub_sequence;
		if (parse_statement_sequence(sub_sequence)) { return true; }
		if_statement->entries.emplace_back(
			sub_expression, std::move(sub_sequence)
		);
	}
	if (token::is(token::keyword_ELSE)) {
		advance();
		stmt::Statement_Sequence else_sequence;
		if (parse_statement_sequence(else_sequence)) { return true; }
		if_statement->entries.emplace_back(nullptr, std::move(else_sequence));
	}
	if (consume(token::keyword_END)) { return true; }
	statement = if_statement;
	return false;
}