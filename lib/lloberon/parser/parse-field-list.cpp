#include "parser/parser.h"

bool Parser::parse_field_list(type::Record_Ptr& record_type) {
	sema::Ident_List ident_list;
	if (parse_ident_list(ident_list)) { return true; }
	if (consume(token::colon)) { return true; }
	type::Type_Ptr type;
	if (parse_type(type)) { return true; }
	for (const auto& id : ident_list) {
		record_type->entries.emplace_back(id.ident, type, id.exported);
	}
	return false;
}