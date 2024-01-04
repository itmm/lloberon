#include "lloberon/parser/parser.h"
#include "lloberon/sema/declaration.h"
#include "lloberon/sema/scope.h"

using namespace lloberon;

bool Parser::parse_module() {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "BOOLEAN", Base_Type_Declaration::bt_BOOLEAN
    } );
    scope.insert(new Base_Type_Declaration {
        "CHAR", Base_Type_Declaration::bt_CHAR
    });
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    scope.insert(new Base_Type_Declaration {
        "REAL", Base_Type_Declaration::bt_REAL
    });
    scope.insert(new Base_Type_Declaration {
        "BYTE", Base_Type_Declaration::bt_BYTE
    });
    scope.insert(new Base_Type_Declaration {
        "SET", Base_Type_Declaration::bt_SET
    });

    if (consume(token::keyword_MODULE)) { return true; }
    if (expect(token::identifier)) { return true; }
    auto module_name { token_.identifier() };
    advance();
    if (consume(token::semicolon)) { return true; }
    if (token_.is(token::keyword_IMPORT)) {
        if (parse_import_list(scope)) { return true; }
    }
    if (parse_declaration_sequence()) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        sema::Statement_Sequence statement_sequence { scope };
        if (parse_statement_sequence(statement_sequence)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    if (expect(token::identifier)) { return true; }
    if (module_name != token_.identifier()) { error(); return true; }
    advance();
    if (consume(token::period)) { return true; }
    if (expect(token::eof)) { return true; }
    return false;
}