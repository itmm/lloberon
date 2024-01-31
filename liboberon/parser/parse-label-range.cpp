#include "parser/parser.h"

sema::Const_Label_Range Parser::parse_label_range() {
	sema::Const_Label_Range range;
	expr::Const_Ptr label { parse_label() };
	range.begin = label;

	if (token::is(token::range)) {
		advance();
		label = parse_label();
		range.end = label;
	} else {
		range.end = range.begin;
	}

	return range;
}