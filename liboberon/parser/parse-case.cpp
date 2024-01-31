#include "parser/parser.h"

void Parser::parse_case(sema::Const_Case& const_case) {
	if (token::is_one_of(token::bar, token::keyword_END)) {
		diag::report(diag::err_bar_in_case_expected);
	}
	sema::Const_Case_List case_list;
	parse_case_list(case_list);

	consume(token::colon);
	const_case.sequence = parse_statement_sequence();
}

void Parser::parse_case(sema::Type_Case& type_case) {
	if (token::is_one_of(token::bar, token::keyword_END)) {
		diag::report(diag::err_bar_in_case_expected);
	}
	parse_case_list(type_case.types);

	consume(token::colon);
	type_case.sequence = parse_statement_sequence();
}