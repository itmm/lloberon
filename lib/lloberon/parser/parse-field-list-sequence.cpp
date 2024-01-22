#include "parser/parser.h"

void Parser::parse_field_list_sequence(type::Record& record_type) {
	parse_field_list(record_type);
	while (token::is(token::semicolon)) {
		advance();
		parse_field_list(record_type);
	}
}