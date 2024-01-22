#include "parser/parser.h"

void Parser::parse_field_list(type::Record_Ptr& record_type) {
	sema::Ident_List ident_list;
	parse_ident_list(ident_list);
	consume(token::colon);
	type::Type_Ptr type;
	parse_type(type);
	for (const auto& id : ident_list) {
		record_type->entries.emplace_back(id.ident, type, id.exported);
	}
}