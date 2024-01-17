#include "parser/parser.h"

#include "type/pointer.h"

bool Parser::parse_pointer_type(type::Type_Ptr& type) {
	if (consume(token::keyword_POINTER)) { return true; }
	if (consume(token::keyword_TO)) { return true; }
	type::Type_Ptr points_to;
	if (parse_type(points_to)) { return true; }
	auto pointed { std::dynamic_pointer_cast<type::Record>(points_to) };
	if (!pointed) {
		return report(diag::err_must_point_to_record);
	}
	type = std::make_shared<type::Pointer>(pointed);
	return false;
}