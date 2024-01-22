#include "parser/parser.h"
#include "stmt/repeat.h"

void Parser::parse_repeat_statement(stmt::Statement_Ptr& statement) {
	auto repeat_statement { std::make_shared<stmt::Repeat>() };
	consume(token::keyword_REPEAT);
	parse_statement_sequence(repeat_statement->statements);
	consume(token::keyword_UNTIL);
	repeat_statement->condition = parse_expression();
	statement = repeat_statement;
}