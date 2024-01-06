#include "decl/base-type.h"

void decl::Base_Type::register_base_types(Scope& scope) {
    scope.insert(std::make_shared<Base_Type>(
            "BOOLEAN", Base_Type::bt_BOOLEAN
    ));
    scope.insert(std::make_shared<Base_Type>(
            "CHAR", Base_Type::bt_CHAR
    ));
    scope.insert(std::make_shared<Base_Type>(
            "INTEGER", Base_Type::bt_INTEGER
    ));
    scope.insert(std::make_shared<Base_Type>(
            "REAL", Base_Type::bt_REAL
    ));
    scope.insert(std::make_shared<Base_Type>(
            "BYTE", Base_Type::bt_BYTE
    ));
    scope.insert(std::make_shared<Base_Type>(
            "SET", Base_Type::bt_SET
    ));
}
