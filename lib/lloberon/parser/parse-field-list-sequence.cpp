#include "parser/parser.h"

bool Parser::parse_field_list_sequence(type::Record_Ptr& record_type) {
	auto entries_on_start { record_type->entries.size() };
	if (parse_field_list(record_type)) { return true; }
	while (token::is(token::semicolon)) {
		advance();
		if (parse_field_list(record_type)) {
			while (record_type->entries.size() > entries_on_start) {
				record_type->entries.pop_back();
			}
			return true;
		}
	}
	return false;
}