#include "parser/parser.h"
#include "stmt/for.h"

bool Parser::parse_for_statement(stmt::Statement_Ptr& statement) {
	auto for_statement { std::make_shared<stmt::For>() };

	if (consume(token::keyword_FOR)) { return true; }
	if (expect(token::identifier)) { return true; }
	for_statement->variable = std::dynamic_pointer_cast<decl::Variable>(
		context::scope->lookup(token::value)
	);
	advance();
	if (consume(token::assign)) { return true; }
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }
	for_statement->begin = expression;
	if (consume(token::keyword_TO)) { return true; }
	if (parse_expression(expression)) { return true; }
	for_statement->end = expression;
	if (token::is(token::keyword_BY)) {
		advance();
		expr::Const_Ptr const_expression;
		if (parse_const_expression(const_expression)) { return true; }
		for_statement->increment = const_expression;
	} else {
		for_statement->increment = expr::Const::create(1);
	}
	if (consume(token::keyword_DO)) { return true; }
	if (parse_statement_sequence(for_statement->statements)) { return true; }
	if (consume(token::keyword_END)) { return true; }
	statement = for_statement;
	return false;
}