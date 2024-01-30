#include "parser/parser.h"

#include "type/pointer.h"

type::Pointer_Ptr Parser::parse_pointer_type() {
	consume(token::keyword_POINTER);
	consume(token::keyword_TO);
	auto points_to { parse_type() };
	auto pointed { std::dynamic_pointer_cast<type::Record>(points_to) };
	if (!pointed) {
		diag::report(diag::err_must_point_to_record);
	}
	return std::make_shared<type::Pointer>(pointed);
}