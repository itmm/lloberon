#include "parser/parser.h"
#include "decl/const.h"

bool Parser::parse_const_declaration(Scope& scope) {
	sema::Ident_Def ident_def;
	if (parse_ident_def(ident_def)) { return true; }
	if (consume(token::equals)) { return true; }
	sema::Const_Expression expression { scope };
	if (parse_const_expression(expression)) { return true; }
	auto declaration { std::make_shared<decl::Const>(expression.expression) };
	declaration->exported = ident_def.exported;
	if (!scope.insert(ident_def.ident, declaration)) {
		diag().report(
			token_.location(), diag::err_already_defined, ident_def.ident
		);
		return true;
	}
	return false;
}