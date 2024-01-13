#include "parser/parser.h"

bool Parser::parse_label_range() {
	Scope scope;
	sema::Const_Label label { scope };
	if (parse_label(label)) { return true; }
	if (token_.is(token::range)) {
		advance();
		if (parse_label(label)) { return true; }
	}
	return false;
}