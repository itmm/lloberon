#include "parser/parser.h"

void Parser::parse_label_range(sema::Const_Label_Range& range) {
	expr::Const_Ptr label;
	parse_label(label);
	range.begin = label;

	if (token::is(token::range)) {
		advance();
		parse_label(label);
		range.end = label;
	} else {
		range.end = range.begin;
	}
}