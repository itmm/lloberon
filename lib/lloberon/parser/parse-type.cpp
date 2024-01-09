#include "parser/parser.h"

bool Parser::parse_type(sema::Type& type) {
    type.clear();
    if (token_.is(token::identifier)) {
        sema::Qual_Ident qual_ident { type.scope() };
        if (parse_qual_ident(qual_ident)) { return true; }
        auto got = std::dynamic_pointer_cast<decl::Type>(qual_ident.declaration);
        if (! got) { error(); return true; }
        type.type = got->type;
    } else if (token_.is(token::keyword_ARRAY)) {
        sema::Array_Type array_type { type.scope() };
        if (parse_array_type(array_type)) { return true; }
    } else if (token_.is(token::keyword_RECORD)) {
        sema::Record_Type record_type { type.scope() };
        if (parse_record_type(record_type)) { return true; }
    } else if (token_.is(token::keyword_POINTER)) {
        if (parse_pointer_type(type)) { return true; }
    } else if (token_.is(token::keyword_PROCEDURE)) {
        sema::Procedure_Type procedure_type { type.scope() };
        if (parse_procedure_type(procedure_type)) { return true; }
    } else { error(); return true; }
    return false;
}