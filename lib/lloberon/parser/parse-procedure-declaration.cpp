#include "parser/parser.h"

bool Parser::parse_procedure_declaration(Context& context) {
	Context sub_context;
	sub_context.scope = std::make_shared<Scope>(context.scope);

	sema::Procedure_Declaration declaration { sub_context };
	if (parse_procedure_heading(declaration)) { return true; }
	if (consume(token::semicolon)) { return true; }
	if (parse_procedure_body(declaration)) { return true; }
	if (expect(token::identifier)) { return true; }
	advance();

	context.scope->insert(declaration.name, declaration.procedure);
	return false;
}