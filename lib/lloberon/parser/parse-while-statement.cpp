#include "parser/parser.h"

bool Parser::parse_while_statement(sema::While_Statement& while_arg) {
	if (consume(token::keyword_WHILE)) { return true; }
	sema::Expression expression { while_arg.scope() };
	if (parse_expression(expression)) { return true; }
	if (consume(token::keyword_DO)) { return true; }
	sema::Statement_Sequence statement_sequence { while_arg.scope() };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	while (token_.is(token::keyword_ELSIF)) {
		advance();
		if (parse_expression(expression)) { return true; }
		if (consume(token::keyword_DO)) { return true; }
		if (parse_statement_sequence(statement_sequence)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	return false;
}