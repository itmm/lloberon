#include "parser/parser.h"
#include "type/array.h"

bool Parser::parse_formal_type(sema::Type& type) {
	int arrays { 0 };
	while (token_.is(token::keyword_ARRAY)) {
		advance();
		if (consume(token::keyword_OF)) { return true; }
		++arrays;
	}
	sema::Qual_Ident qual_ident { type.scope };
	if (parse_qual_ident(qual_ident)) { return true; }
	auto decl_type {
		std::dynamic_pointer_cast<decl::Type>(qual_ident.declaration)
	};
	if (! decl_type) {
		diag().report(token_.location(), diag::err_type_expected);
		return true;
	}
	auto current { decl_type->type };
	for (; arrays; --arrays) {
		current = std::make_shared<type::Array>(-1, current);
	}
	type.type = current;
	return false;
}