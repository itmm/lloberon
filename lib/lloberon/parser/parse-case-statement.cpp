#include "parser/parser.h"
#include "stmt/case.h"
#include "type/pointer.h"
#include "type/record.h"

stmt::Statement_Ptr Parser::parse_case_statement() {
	consume(token::keyword_CASE);
	expr::Expression_Ptr expression { parse_expression() };

	const auto& type { expression->type };
	if (
		std::dynamic_pointer_cast<type::Pointer>(type) ||
		    std::dynamic_pointer_cast<type::Record>(type)>(type)
	) {
		auto case_statement { std::make_shared<stmt::Type_Case>() };
		case_statement->condition = expression;

		consume(token::keyword_OF);
		sema::Type_Case type_case;
		parse_case(type_case);
		while (token::is(token::bar)) {
			advance();
			parse_case(type_case);
		}
		consume(token::keyword_END);

		return case_statement;
	} else {
		auto case_statement { std::make_shared<stmt::Const_Case>() };
		case_statement->condition = expression;

		consume(token::keyword_OF);
		sema::Const_Case const_case;
		parse_case(const_case);
		while (token::is(token::bar)) {
			advance();
			parse_case(const_case);
		}
		consume(token::keyword_END);

		return case_statement;
	}
}