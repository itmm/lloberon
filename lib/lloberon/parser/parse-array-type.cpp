#include <vector>

#include "parser/parser.h"
#include "type/array.h"

bool Parser::parse_array_type(type::Type_Ptr& type) {
	std::vector<int> counts;
	if (consume(token::keyword_ARRAY)) { return true; }
	int length;
	if (parse_length(length)) { return true; }
	counts.push_back(length);
	while (token::is(token::comma)) {
		advance();
		if (parse_length(length)) { return true; }
		counts.push_back(length);
	}
	if (consume(token::keyword_OF)) { return true; }
	type::Type_Ptr base;
	if (parse_type(base)) { return true; }
	type::Type_Ptr current { base };
	for (auto i { counts.size() }; i; --i) {
		auto array { std::make_shared<type::Array>(counts[i - 1], current) };
		current = array;
	}
	type = current;
	return false;
}