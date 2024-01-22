#include "parser/parser.h"

void Parser::parse_record_type(type::Type_Ptr& type) {
	auto record_type { std::make_shared<type::Record>() };
	consume(token::keyword_RECORD);
	if (token::is(token::left_parenthesis)) {
		advance();
		parse_base_type(record_type);
		consume(token::right_parenthesis);
	}
	if (!token::is(token::keyword_END)) {
		parse_field_list_sequence(record_type);
	}
	consume(token::keyword_END);
	type = record_type;
}