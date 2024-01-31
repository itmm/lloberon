#include "parser/parser.h"

void Parser::parse_procedure_declaration() {
	sema::Procedure_Declaration declaration;

	{
		context::Push_Scope pushed_scope {
			std::make_shared<Scope>(context::scope)
		};

		parse_procedure_heading(declaration);
		consume(token::semicolon);
		parse_procedure_body(declaration);
		expect(token::identifier);
		advance();
	}
	context::scope->insert(declaration.name, declaration.procedure);
}