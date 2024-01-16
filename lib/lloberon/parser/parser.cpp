#include "parser/parser.h"
#include "decl/procedure.h"
#include "decl/type.h"

bool Parser::parse() {
	Context context;
	decl::Procedure::register_base_procedures(*context.scope);
	decl::Type::register_base_types(*context.scope);

	return parse_module(context);
}