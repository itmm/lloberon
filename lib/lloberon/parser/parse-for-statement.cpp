#include "parser/parser.h"
#include "stmt/for.h"

bool Parser::parse_for_statement(sema::Statement& statement) {
	auto for_statement { std::make_shared<stmt::For>() };

	if (consume(token::keyword_FOR)) { return true; }
	if (expect(token::identifier)) { return true; }
	for_statement->variable = std::dynamic_pointer_cast<decl::Variable>(
		statement.context.scope->lookup(token::value)
	);
	advance();
	if (consume(token::assign)) { return true; }
	sema::Expression expression { statement.context };
	if (parse_expression(expression)) { return true; }
	for_statement->begin = expression.expression;
	if (consume(token::keyword_TO)) { return true; }
	if (parse_expression(expression)) { return true; }
	for_statement->end = expression.expression;
	if (token::is(token::keyword_BY)) {
		advance();
		sema::Const_Expression const_expression { statement.context };
		if (parse_const_expression(const_expression)) { return true; }
		for_statement->increment = const_expression.expression;
	} else {
		for_statement->increment = expr::Const::create(1);
	}
	if (consume(token::keyword_DO)) { return true; }
	sema::Statement_Sequence statement_sequence { statement.context };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	for_statement->statements = std::move(statement_sequence.sequence);
	if (consume(token::keyword_END)) { return true; }
	statement.statement = for_statement;
	return false;
}