#include "parser/parser.h"

bool Parser::parse_case_list(sema::Const_Case_List& case_list) {
	sema::Const_Label_Range range { case_list.scope };
	if (parse_label_range(range)) { return true; }
	case_list.entries.emplace_back(range.begin, range.end);
	while (token_.is(token::comma)) {
		advance();
		if (parse_label_range(range)) { return true; }
		case_list.entries.emplace_back(range.begin, range.end);
	}
	return false;
}

bool Parser::parse_case_list(sema::Type_Case_List& case_list) {
	sema::Type type { case_list.scope };
	if (parse_type(type)) { return true;}
	case_list.entries.push_back(type.type);
	while (token_.is(token::comma)) {
		advance();
		if (parse_type(type)) { return true; }
		case_list.entries.push_back(type.type);
	}
	return false;
}