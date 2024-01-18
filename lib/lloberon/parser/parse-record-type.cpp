#include "parser/parser.h"

bool Parser::parse_record_type(type::Type_Ptr& type) {
	auto record_type { std::make_shared<type::Record>() };
	if (consume(token::keyword_RECORD)) { return true; }
	if (token::is(token::left_parenthesis)) {
		advance();
		if (parse_base_type(record_type)) { return true; }
		if (consume(token::right_parenthesis)) { return true; }
	}
	if (!token::is(token::keyword_END)) {
		if (parse_field_list_sequence(record_type)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	type = record_type;
	return false;
}