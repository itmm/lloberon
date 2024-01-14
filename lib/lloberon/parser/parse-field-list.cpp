#include "parser/parser.h"

bool Parser::parse_field_list(sema::Record_Type& record_type) {
	sema::Ident_List ident_list;
	if (parse_ident_list(ident_list)) { return true; }
	if (consume(token::colon)) { return true; }
	sema::Type type { record_type.scope };
	if (parse_type(type)) { return true; }
	for (const auto& id : ident_list) {
		record_type.record->entries.emplace_back(
			id.ident, type.type, id.exported
		);
	}
	return false;
}