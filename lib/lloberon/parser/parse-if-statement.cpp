#include "parser/parser.h"
#include "stmt/if.h"

void Parser::parse_if_statement(stmt::Statement_Ptr& statement) {
	auto if_statement { std::make_shared<stmt::If>() };
	consume(token::keyword_IF);
	expr::Expression_Ptr expression { parse_expression() };
	consume(token::keyword_THEN);
	stmt::Statement_Sequence statement_sequence;
	parse_statement_sequence(statement_sequence);
	if_statement->entries.emplace_back(
		expression, std::move(statement_sequence)
	);
	while (token::is(token::keyword_ELSIF)) {
		advance();
		expr::Expression_Ptr sub_expression { parse_expression() };
		consume(token::keyword_THEN);
		stmt::Statement_Sequence sub_sequence;
		parse_statement_sequence(sub_sequence);
		if_statement->entries.emplace_back(
			sub_expression, std::move(sub_sequence)
		);
	}
	if (token::is(token::keyword_ELSE)) {
		advance();
		stmt::Statement_Sequence else_sequence;
		parse_statement_sequence(else_sequence);
		if_statement->entries.emplace_back(nullptr, std::move(else_sequence));
	}
	consume(token::keyword_END);
	statement = if_statement;
}