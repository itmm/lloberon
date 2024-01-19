#include "parser/parser.h"

bool Parser::parse_case(sema::Const_Case& const_case) {
	if (token::is_one_of(token::bar, token::keyword_END)) {
		return report(diag::err_bar_in_case_expected);
	}
	sema::Const_Case_List case_list;
	if (parse_case_list(case_list)) { return true; }

	if (consume(token::colon)) { return true; }
	if (parse_statement_sequence(const_case.sequence)) { return true; }
	return false;
}

bool Parser::parse_case(sema::Type_Case& type_case) {
	if (token::is_one_of(token::bar, token::keyword_END)) {
		return report(diag::err_bar_in_case_expected);
	}
	if (parse_case_list(type_case.types)) { return true; }

	if (consume(token::colon)) { return true; }
	if (parse_statement_sequence(type_case.sequence)) { return true; }

	return false;
}