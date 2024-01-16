#include "parser/parser.h"

bool Parser::parse_field_list_sequence(sema::Record_Type& record_type) {
	auto entries_on_start { record_type.record->entries.size() };
	if (parse_field_list(record_type)) { return true; }
	while (token::is(token::semicolon)) {
		advance();
		if (parse_field_list(record_type)) {
			while (record_type.record->entries.size() > entries_on_start) {
				record_type.record->entries.pop_back();
			}
			return true;
		}
	}
	return false;
}