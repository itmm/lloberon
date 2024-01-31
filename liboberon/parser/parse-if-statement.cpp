#include "parser/parser.h"
#include "stmt/if.h"

stmt::If_Ptr Parser::parse_if_statement() {
	auto if_statement { std::make_shared<stmt::If>() };
	consume(token::keyword_IF);
	expr::Expression_Ptr expression { parse_expression() };
	consume(token::keyword_THEN);
	if_statement->entries.emplace_back(
		expression, parse_statement_sequence()
	);
	while (token::is(token::keyword_ELSIF)) {
		advance();
		expr::Expression_Ptr sub_expression { parse_expression() };
		consume(token::keyword_THEN);
		if_statement->entries.emplace_back(
			sub_expression, parse_statement_sequence()
		);
	}
	if (token::is(token::keyword_ELSE)) {
		advance();
		if_statement->entries.emplace_back(nullptr, parse_statement_sequence());
	}
	consume(token::keyword_END);
	return if_statement;
}