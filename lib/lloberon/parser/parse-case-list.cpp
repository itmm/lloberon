#include "parser/parser.h"

bool Parser::parse_case_list(sema::Const_Case_List& case_list) {
	sema::Const_Label_Range range;
	if (parse_label_range(range)) { return true; }
	case_list.emplace_back(range.begin, range.end);
	while (token::is(token::comma)) {
		advance();
		if (parse_label_range(range)) { return true; }
		case_list.emplace_back(range.begin, range.end);
	}
	return false;
}

bool Parser::parse_case_list(sema::Type_Case_List& case_list) {
	type::Type_Ptr type;
	if (parse_type(type)) { return true;}
	case_list.push_back(type);
	while (token::is(token::comma)) {
		advance();
		if (parse_type(type)) { return true; }
		case_list.push_back(type);
	}
	return false;
}