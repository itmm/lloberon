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
	parse_statement_sequence(for_statement->statements);
	consume(token::keyword_END);
	statement = for_statement;
}