#include "parser/parser.h"

void Parser::parse_field_list(type::Record& record_type) {
	auto ident_list { parse_ident_list() };
	consume(token::colon);
	auto type { parse_type() };
	for (const auto& id : ident_list) {
		record_type.entries.emplace_back(id.ident, type, id.exported);
	}
}