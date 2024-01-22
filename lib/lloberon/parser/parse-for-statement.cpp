#include "parser/parser.h"
#include "stmt/for.h"

void Parser::parse_for_statement(stmt::Statement_Ptr& statement) {
	auto for_statement { std::make_shared<stmt::For>() };

	consume(token::keyword_FOR);
	expect(token::identifier);
	for_statement->variable = std::dynamic_pointer_cast<expr::Variable>(
		context::scope->lookup(token::value)
	);
	if (!for_statement->variable) {
		diag::report(diag::err_variable_expected);
	}
	advance();
	consume(token::assign);
	expr::Expression_Ptr expression;
	parse_expression(expression);
	for_statement->begin = expression;
	consume(token::keyword_TO);
	parse_expression(expression);
	for_statement->end = expression;
	if (token::is(token::keyword_BY)) {
		advance();
		expr::Const_Ptr const_expression;
		parse_const_expression(const_expression);
		for_statement->increment = const_expression;
	} else {
		for_statement->increment = expr::Const::create(1);
	}
	consume(token::keyword_DO);
	parse_statement_sequence(for_statement->statements);
	consume(token::keyword_END);
	statement = for_statement;
}