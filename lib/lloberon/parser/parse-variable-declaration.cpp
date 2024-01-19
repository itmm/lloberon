#include "parser/parser.h"

bool Parser::parse_variable_declaration() {
	sema::Ident_List ident_list;
	if (parse_ident_list(ident_list)) { return true; }
	if (consume(token::colon)) { return true; }
	type::Type_Ptr type;
	if (parse_type(type)) { return true; }

	for (const auto& id: ident_list) {
		if (!context::scope->insert(
			id, std::make_shared<expr::Variable>(type)
		)) {
			return report(diag::err_already_defined);
		}
	}
	return false;
}