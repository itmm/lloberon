#include <vector>

#include "parser/parser.h"
#include "type/array.h"

void Parser::parse_array_type(type::Type_Ptr& type) {
	std::vector<int> counts;
	consume(token::keyword_ARRAY);
	int length { parse_length() };
	counts.push_back(length);
	while (token::is(token::comma)) {
		advance();
		length = parse_length();
		counts.push_back(length);
	}
	consume(token::keyword_OF);
	type::Type_Ptr base;
	parse_type(base);
	type::Type_Ptr current { base };
	for (auto i { counts.size() }; i; --i) {
		auto array { std::make_shared<type::Array>(counts[i - 1], current) };
		current = array;
	}
	type = current;
}