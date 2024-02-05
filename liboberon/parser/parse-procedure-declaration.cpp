#include "parser/parser.h"
#include "type/reference.h"

void Parser::parse_procedure_declaration() {
	auto procedure { std::make_shared<decl::Procedure>() };
	consume(token::keyword_PROCEDURE);
	auto name { parse_ident_def() };
	context::scope->insert(name, procedure);

	{
		context::Push_Scope pushed_scope { procedure->scope };

		parse_formal_parameters(*procedure);
		consume(token::semicolon);
		for (const auto& param : procedure->parameters) {
			auto type {
				param.reference ?
					std::make_shared<type::Reference>(param.type) :
					param.type
			};
			procedure->insert(
				param.name, std::make_shared<expr::Variable>(type)
			);
		}

		parse_procedure_body(*procedure);
		expect(token::identifier);
		if (token::value != name.ident) {
			diag::report(
				diag::err_procedure_names_dont_match, name.ident, token::value
			);
		}
		advance();
	}
}