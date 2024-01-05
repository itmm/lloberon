#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_case_list(sema::Case_List& case_list) {
    if (parse_label_range()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_label_range()) { return true; }
    }
    return false;
}