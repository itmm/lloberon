#include "parser/parser.h"
#include "decl/procedure.h"

bool Parser::parse() {
	context::clear();
	decl::Procedure::register_base_procedures(*context::scope);
	context::scope->register_base_types();

	return parse_module();
}