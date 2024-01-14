#include "parser/parser.h"

bool Parser::parse_formal_parameters(
	sema::Procedure_Type& procedure_type
) {
	if (consume(token::left_parenthesis)) { return true; }
	if (!token_.is(token::right_parenthesis)) {
		if (parse_formal_parameter_section(procedure_type)) { return true; }
		while (token_.is(token::semicolon)) {
			advance();
			if (parse_formal_parameter_section(procedure_type)) { return true; }
		}
	}
	if (consume(token::right_parenthesis)) { return true; }
	if (token_.is(token::colon)) {
		advance();
		sema::Qual_Ident qual_ident { procedure_type.scope };
		if (parse_qual_ident(qual_ident)) { return true; }
		auto return_type { std::dynamic_pointer_cast<decl::Type>(
			qual_ident.declaration
		) };

		if (! return_type) {
			diag().report(token_.location(), diag::err_type_expected);
			return true;
		}
		procedure_type.procedure->return_type = return_type->type;
	}
	return false;
}