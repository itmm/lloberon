#include "parser/parser.h"
#include "decl/variable.h"

bool Parser::parse_variable_declaration(Scope& scope) {
	sema::Ident_List ident_list;
	if (parse_ident_list(ident_list)) { return true; }
	if (consume(token::colon)) { return true; }
	sema::Type type { scope };
	if (parse_type(type)) { return true; }

	for (const auto& id: ident_list) {
		if (!scope.insert(id, std::make_shared<decl::Variable>(type.type))) {
			diag().report(token_.location(), diag::err_already_defined);
			return true;
		}
	}
	return false;
}