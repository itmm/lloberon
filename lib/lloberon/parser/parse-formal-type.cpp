#include "parser/parser.h"
#include "type/array.h"

bool Parser::parse_formal_type(type::Type_Ptr& type) {
	int arrays { 0 };
	while (token::is(token::keyword_ARRAY)) {
		advance();
		if (consume(token::keyword_OF)) { return true; }
		++arrays;
	}
	sema::Qual_Ident qual_ident;
	if (parse_qual_ident(qual_ident)) { return true; }
	auto decl_type {
		std::dynamic_pointer_cast<decl::Type>(qual_ident.declaration)
	};
	if (! decl_type) {
		return report(diag::err_type_expected);
	}
	auto current { decl_type->type };
	for (; arrays; --arrays) {
		current = std::make_shared<type::Array>(-1, current);
	}
	type = current;
	return false;
}