#include "parser/parser.h"

bool Parser::parse_statement(sema::Statement& statement) {
	if (token_.is(token::identifier)) {
		sema::Assignment_Or_Procedure_Call assignment_or_procedure_call {
			statement.scope()
		};
		if (parse_assignment_or_procedure_call(assignment_or_procedure_call)) {
			return true;
		}
	} else if (token_.is(token::keyword_IF)) {
		if (parse_if_statement(statement)) { return true; }
	} else if (token_.is(token::keyword_CASE)) {
		sema::Case_Statement case_statement { statement.scope() };
		if (parse_case_statement(case_statement)) { return true; }
	} else if (token_.is(token::keyword_WHILE)) {
		sema::While_Statement while_statement { statement.scope() };
		if (parse_while_statement(while_statement)) { return true; }
	} else if (token_.is(token::keyword_REPEAT)) {
		if (parse_repeat_statement(statement)) { return true; }
	} else if (token_.is(token::keyword_FOR)) {
		if (parse_for_statement(statement)) { return true; }
	}
	return false;
}
