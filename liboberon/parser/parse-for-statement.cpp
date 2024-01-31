#include "parser/parser.h"
#include "stmt/for.h"

stmt::For_Ptr Parser::parse_for_statement() {
	auto for_statement { std::make_shared<stmt::For>() };

	consume(token::keyword_FOR);
	expect(token::identifier);
	for_statement->variable = expr::Variable::as_variable(
		context::scope->lookup(token::value)
	);
	if (!for_statement->variable) {
		diag::report(diag::err_variable_expected);
	}
	advance();
	consume(token::assign);
	for_statement->begin = parse_expression();
	consume(token::keyword_TO);
	for_statement->end = parse_expression();
	if (token::is(token::keyword_BY)) {
		advance();
		for_statement->increment = parse_const_expression();
	} else {
		for_statement->increment = expr::Const::create(1);
	}
	consume(token::keyword_DO);
	for_statement->statements = parse_statement_sequence();
	consume(token::keyword_END);
	return for_statement;
}