#include "parser/parser.h"

#include "type/pointer.h"

bool Parser::parse_pointer_type(sema::Type& type) {
	if (consume(token::keyword_POINTER)) { return true; }
	if (consume(token::keyword_TO)) { return true; }
	sema::Type points_to { type.context };
	if (parse_type(points_to)) { return true; }
	auto pointed { std::dynamic_pointer_cast<type::Record>(points_to.type) };
	if (!pointed) {
		return report(diag::err_must_point_to_record);
	}
	type.type = std::make_shared<type::Pointer>(pointed);
	return false;
}