#include "parser/parser.h"

type::Type_Ptr Parser::parse_type() {
	if (token::is(token::identifier)) {
		auto got { type::Type::as_type(parse_qual_ident()) };
		if (!got) { diag::report(diag::err_identifier_must_be_type); }
		return got;
	} else if (token::is(token::keyword_ARRAY)) {
		return parse_array_type();
	} else if (token::is(token::keyword_RECORD)) {
		return parse_record_type();
	} else if (token::is(token::keyword_POINTER)) {
		return parse_pointer_type();
	} else if (token::is(token::keyword_PROCEDURE)) {
		return parse_procedure_type();
	} else {
		diag::report(diag::err_type_expected);
	}
}