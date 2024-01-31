#include "parser/parser.h"

void Parser::parse_case_list(sema::Const_Case_List& case_list) {
	sema::Const_Label_Range range { parse_label_range() };
	case_list.emplace_back(range.begin, range.end);
	while (token::is(token::comma)) {
		advance();
		range = parse_label_range();
		case_list.emplace_back(range.begin, range.end);
	}
}

void Parser::parse_case_list(sema::Type_Case_List& case_list) {
	case_list.push_back(parse_type());
	while (token::is(token::comma)) {
		advance();
		case_list.push_back(parse_type());
	}
}