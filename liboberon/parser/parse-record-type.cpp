#include "parser/parser.h"

type::Record_Ptr Parser::parse_record_type() {
	auto record_type { std::make_shared<type::Record>() };
	consume(token::keyword_RECORD);
	if (token::is(token::left_parenthesis)) {
		advance();
		record_type->base = parse_base_type();
		consume(token::right_parenthesis);
	}
	if (!token::is(token::keyword_END)) {
		parse_field_list_sequence(*record_type);
	}
	consume(token::keyword_END);
	return record_type;
}