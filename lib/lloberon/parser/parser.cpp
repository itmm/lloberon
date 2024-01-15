#include "parser/parser.h"
#include "decl/type.h"

bool Parser::parse() {
	Context context;
	decl::Type::register_base_types(*context.scope);

	return parse_module(context);
}