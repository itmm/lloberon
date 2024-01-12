#include "parser/parser.h"

bool Parser::parse_procedure_declaration(Scope& scope) {
	sema::Procedure_Declaration declaration { scope };
	if (parse_procedure_heading(declaration)) { return true; }
	if (consume(token::semicolon)) { return true; }
	if (parse_procedure_body(declaration)) { return true; }
	if (expect(token::identifier)) { return true; }
	advance();
	scope.insert(declaration.name, declaration.procedure);
	return false;
}