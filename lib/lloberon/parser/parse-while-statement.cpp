#include "parser/parser.h"
#include "stmt/while.h"

stmt::While_Ptr Parser::parse_while_statement() {
	auto while_statement { std::make_shared<stmt::While>() };
	consume(token::keyword_WHILE);
	expr::Expression_Ptr expression { parse_expression() };
	consume(token::keyword_DO);
	while_statement->entries.emplace_back(
		expression, parse_statement_sequence()
	);
	while (token::is(token::keyword_ELSIF)) {
		advance();
		expression = parse_expression();
		consume(token::keyword_DO);
		while_statement->entries.emplace_back(
			expression, parse_statement_sequence()
		);
	}
	consume(token::keyword_END);
	return while_statement;
}