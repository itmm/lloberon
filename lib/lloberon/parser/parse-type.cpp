#include "parser/parser.h"

bool Parser::parse_type(sema::Type& type) {
	if (token::is(token::identifier)) {
		sema::Qual_Ident qual_ident { type.context };
		if (parse_qual_ident(qual_ident)) { return true; }
		auto got = std::dynamic_pointer_cast<decl::Type>(
			qual_ident.declaration
		);
		if (!got) {
			return report(diag::err_identifier_must_be_type);
		}
		type.type = got->type;
	} else if (token::is(token::keyword_ARRAY)) {
		if (parse_array_type(type)) { return true; }
	} else if (token::is(token::keyword_RECORD)) {
		if (parse_record_type(type)) { return true; }
	} else if (token::is(token::keyword_POINTER)) {
		if (parse_pointer_type(type)) { return true; }
	} else if (token::is(token::keyword_PROCEDURE)) {
		if (parse_procedure_type(type)) { return true; }
	} else {
		return report(diag::err_type_expected);
	}
	return false;
}