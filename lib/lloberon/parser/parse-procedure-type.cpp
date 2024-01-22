#include "parser/parser.h"

void Parser::parse_procedure_type(type::Type_Ptr& type) {
	type::Procedure_Ptr procedure_type;
	consume(token::keyword_PROCEDURE);
	parse_formal_parameters(procedure_type);
	type = procedure_type;
}