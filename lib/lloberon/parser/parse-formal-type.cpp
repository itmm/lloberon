#include "parser/parser.h"
#include "type/array.h"

void Parser::parse_formal_type(type::Type_Ptr& type) {
	int arrays { 0 };
	while (token::is(token::keyword_ARRAY)) {
		advance();
		consume(token::keyword_OF);
		++arrays;
	}
	auto decl_type { type::Type::as_type(parse_qual_ident()) };
	if (! decl_type) { diag::report(diag::err_type_expected); }
	auto current { decl_type };
	for (; arrays; --arrays) {
		current = std::make_shared<type::Array>(-1, current);
	}
	type = current;
}