#include "parser/parser.h"
#include "stmt/case.h"

bool Parser::parse_case_statement(sema::Statement& statement) {
	auto& scope { statement.scope() };
	auto case_statement { std::make_shared<stmt::Case>() };

	if (consume(token::keyword_CASE)) { return true; }
	sema::Expression expression { scope };
	if (parse_expression(expression)) { return true; }
	case_statement->condition = expression.expression;

	if (consume(token::keyword_OF)) { return true; }
	sema::Case case_arg { scope };
	if (parse_case(case_arg)) { return true; }
	while (token_.is(token::bar)) {
		advance();
		if (parse_case(case_arg)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }

	statement.statement = case_statement;
	return false;
}