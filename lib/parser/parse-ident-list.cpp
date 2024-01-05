#include "parser/parser.h"
#include "sema/ident-def.h"

bool Parser::parse_ident_list(lloberon::sema::Ident_List& ident_list) {
    ident_list.clear();
    lloberon::sema::Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    ident_list.push_back(ident_def);
    while (token_.is(token::comma)) {
        advance();
        if (parse_ident_def(ident_def)) { ident_list.clear(); return true; }
        ident_list.push_back(ident_def);
    }
    return false;
}