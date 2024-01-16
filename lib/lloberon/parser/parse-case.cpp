#include "parser/parser.h"

bool Parser::parse_case(sema::Const_Case& const_case) {
	if (token::is_one_of(token::bar, token::keyword_END)) {
		diag().report(token_.location(), diag::err_bar_in_case_expected);
		return true;
	}
	sema::Const_Case_List case_list { const_case.context };
	if (parse_case_list(case_list)) { return true; }

	if (consume(token::colon)) { return true; }
	sema::Statement_Sequence statement_sequence { const_case.context };
	if (parse_statement_sequence(statement_sequence)) { return true; }
	return false;
}

bool Parser::parse_case(sema::Type_Case& type_case) {
	if (token::is_one_of(token::bar, token::keyword_END)) {
		diag().report(token_.location(), diag::err_bar_in_case_expected);
		return true;
	}
	sema::Type_Case_List case_list { type_case.context };
	if (parse_case_list(case_list)) { return true; }

	if (consume(token::colon)) { return true; }
	sema::Statement_Sequence statement_sequence { type_case.context };
	if (parse_statement_sequence(statement_sequence)) { return true; }

	type_case.types = std::move(case_list.entries);
	type_case.sequence = std::move(statement_sequence.sequence);

	return false;
}