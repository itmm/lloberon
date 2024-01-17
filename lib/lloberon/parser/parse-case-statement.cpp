#include "parser/parser.h"
#include "stmt/case.h"
#include "type/pointer.h"
#include "type/record.h"

bool Parser::parse_case_statement(sema::Statement& statement) {
	if (consume(token::keyword_CASE)) { return true; }
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }

	const auto& type { expression->type };
	if (
		std::dynamic_pointer_cast<type::Pointer>(type) ||
		    std::dynamic_pointer_cast<type::Record>(type)>(type)
	) {
		auto case_statement { std::make_shared<stmt::Type_Case>() };
		case_statement->condition = expression;

		if (consume(token::keyword_OF)) { return true; }
		sema::Type_Case type_case;
		if (parse_case(type_case)) { return true; }
		while (token::is(token::bar)) {
			advance();
			if (parse_case(type_case)) { return true; }
		}
		if (consume(token::keyword_END)) { return true; }

		statement.statement = case_statement;
	} else {
		auto case_statement { std::make_shared<stmt::Const_Case>() };
		case_statement->condition = expression;

		if (consume(token::keyword_OF)) { return true; }
		sema::Const_Case const_case;
		if (parse_case(const_case)) { return true; }
		while (token::is(token::bar)) {
			advance();
			if (parse_case(const_case)) { return true; }
		}
		if (consume(token::keyword_END)) { return true; }

		statement.statement = case_statement;
	}
	return false;
}