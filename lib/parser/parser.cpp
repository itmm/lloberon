#include "parser/parser.h"

bool Parser::parse() {
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

    return parse_module(scope);
}