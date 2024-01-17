#include "parser/parser.h"

bool Parser::parse_label_range(sema::Const_Label_Range& range) {
	sema::Const_Label label;
	if (parse_label(label)) { return true; }
	range.begin = label.value;

	if (token::is(token::range)) {
		advance();
		if (parse_label(label)) { return true; }
		range.end = label.value;
	} else {
		range.end = range.begin;
	}
	return false;
}