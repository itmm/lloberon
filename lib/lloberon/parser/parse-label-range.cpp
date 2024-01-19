#include "parser/parser.h"

bool Parser::parse_label_range(sema::Const_Label_Range& range) {
	expr::Const_Ptr label;
	if (parse_label(label)) { return true; }
	range.begin = label;

	if (token::is(token::range)) {
		advance();
		if (parse_label(label)) { return true; }
		range.end = label;
	} else {
		range.end = range.begin;
	}
	return false;
}