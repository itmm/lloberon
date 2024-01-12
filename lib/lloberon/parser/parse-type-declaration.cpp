#include "parser/parser.h"

bool Parser::parse_type_declaration(Scope& scope) {
	sema::Ident_Def ident_def;
	if (parse_ident_def(ident_def)) { return true; }
	if (scope.has_in_scope(ident_def.ident)) {
		diag().report(token_.location(), diag::err_already_defined);
		return true;
	}
	if (consume(token::equals)) { return true; }
	sema::Type type { scope };
	if (parse_type(type)) { return true; }
	auto declaration { std::make_shared<decl::Type>(type.type) };
	declaration->exported = ident_def.exported;
	scope.insert(ident_def.ident, declaration);
	return false;
}