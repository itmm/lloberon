#include "parser/parser.h"

bool Parser::parse_formal_parameters(sema::Formal_Parameters& formal_parameters) {
    if (consume(token::left_parenthesis)) { return true; }
    if (!token_.is(token::right_parenthesis)) {
        sema::Formal_Parameter_Section formal_parameter_section { formal_parameters.scope() };
        if (parse_formal_parameter_section(formal_parameter_section)) { return true; }
        while (token_.is(token::semicolon)) {
            advance();
            if (parse_formal_parameter_section(formal_parameter_section)) { return true; }
        }
    }
    if (consume(token::right_parenthesis)) { return true; }
    if (token_.is(token::colon)) {
        advance();
        sema::Qual_Ident qual_ident { formal_parameters.scope() };
        if (parse_qual_ident(qual_ident)) { return true; }
    }
    return false;
}