#include "parser/parser.h"

bool Parser::parse_procedure_type(type::Type_Ptr& type) {
	type::Procedure_Ptr procedure_type;
	if (consume(token::keyword_PROCEDURE)) { return true; }
	if (parse_formal_parameters(procedure_type)) { return true; }
	type = procedure_type;
	return false;
}