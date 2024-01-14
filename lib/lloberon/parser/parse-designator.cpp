#include "parser/parser.h"

bool Parser::parse_designator(sema::Designator& designator) {
	sema::Qual_Ident qual_ident { designator.scope() };
	if (parse_qual_ident(qual_ident)) { return true; }
	for (;;) {
		if (token_.is(token::period)) {
			advance();
			if (consume(token::identifier)) { return true; }
		} else if (token_.is(token::left_bracket)) {
			advance();
			sema::Expression_List expression_list { designator.scope() };
			if (parse_expression_list(expression_list)) { return true; }
			if (consume(token::right_bracket)) { return true; }
		} else if (token_.is(token::ptr)) {
			advance();
//        } else if (token_.is(token::left_parenthesis)) {
//            advance();
//            parse_qualident();
//            if (consume(token::right_parenthesis)) { return; }
		} else { break; }
	}
	return false;
}