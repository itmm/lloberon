#include "parser/parser.h"
#include "stmt/if.h"

bool Parser::parse_if_statement(sema::Statement& statement) {
	auto& scope { statement.scope() };
	auto if_statement { std::make_shared<stmt::If>() };
	if (consume(token::keyword_IF)) { return true; }
	sema::Expression expression { scope };
	if (parse_expression(expression)) { return true; }
	if (consume(token::keyword_THEN)) { return true; }
	sema::Statement_Sequence statement_sequence { scope };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	if_statement->entries.emplace_back(
		expression.expression, std::move(statement_sequence.sequence)
	);
	while (token_.is(token::keyword_ELSIF)) {
		advance();
		sema::Expression sub_expression { scope };
		if (parse_expression(sub_expression)) { return true; }
		if (consume(token::keyword_THEN)) { return true; }
		sema::Statement_Sequence sub_sequence { scope };
		if (parse_statement_sequence(sub_sequence)) { return true; }
		if_statement->entries.emplace_back(
			sub_expression.expression, std::move(sub_sequence.sequence)
		);
	}
	if (token_.is(token::keyword_ELSE)) {
		advance();
		sema::Statement_Sequence else_sequence { scope };
		if (parse_statement_sequence(else_sequence)) { return true; }
		if_statement->entries.emplace_back(
			nullptr, std::move(else_sequence.sequence)
		);
	}
	if (consume(token::keyword_END)) { return true; }
	statement.statement = if_statement;
	return false;
}