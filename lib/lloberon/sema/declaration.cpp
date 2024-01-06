#include "sema/declaration.h"

void Base_Type_Declaration::register_base_types(Scope& scope) {
    scope.insert(std::make_shared<Base_Type_Declaration>(
            "BOOLEAN", Base_Type_Declaration::bt_BOOLEAN
    ));
    scope.insert(std::make_shared<Base_Type_Declaration>(
            "CHAR", Base_Type_Declaration::bt_CHAR
    ));
    scope.insert(std::make_shared<Base_Type_Declaration>(
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    ));
    scope.insert(std::make_shared<Base_Type_Declaration>(
            "REAL", Base_Type_Declaration::bt_REAL
    ));
    scope.insert(std::make_shared<Base_Type_Declaration>(
            "BYTE", Base_Type_Declaration::bt_BYTE
    ));
    scope.insert(std::make_shared<Base_Type_Declaration>(
            "SET", Base_Type_Declaration::bt_SET
    ));
}
