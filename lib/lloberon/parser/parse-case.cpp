#include "parser/parser.h"

bool Parser::parse_case(sema::Case& case_arg) {
	if (token_.is_one_of(token::bar, token::keyword_END)) {
		diag().report(token_.location(), diag::err_bar_in_case_expected);
		return true;
	}
	sema::Case_List case_list { case_arg.scope() };
	if (parse_case_list(case_list)) { return true; }
	if (consume(token::colon)) { return true; }
	sema::Statement_Sequence statement_sequence { case_arg.scope() };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	return false;
}