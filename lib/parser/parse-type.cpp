#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_type() {
    if (token_.is(token::identifier)) {
        if (parse_qual_ident()) { return true; }
    } else if (token_.is(token::keyword_ARRAY)) {
        if (parse_array_type()) { return true; }
    } else if (token_.is(token::keyword_RECORD)) {
        if (parse_record_type()) { return true; }
    } else if (token_.is(token::keyword_POINTER)) {
        if (parse_pointer_type()) { return true; }
    } else if (token_.is(token::keyword_PROCEDURE)) {
        if (parse_procedure_type()) { return true; }
    } else { error(); return true; }
    return false;
}