#include "parser/parser.h"
#include "sema/ident-def.h"

bool Parser::parse_procedure_heading(
	sema::Procedure_Heading& procedure_heading
) {
	if (consume(token::keyword_PROCEDURE)) { return true; }
	sema::Ident_Def ident_def;
	if (parse_ident_def(ident_def)) { return true; }
	sema::Procedure_Type procedure_type { procedure_heading.scope() };
	if (parse_formal_parameters(procedure_type)) { return true; }
	return false;
}