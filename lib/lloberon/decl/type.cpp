#include "decl/type.h"
#include "sema/scope.h"
#include "type/base.h"

void decl::Type::register_base_types(Scope& scope) {
    scope.insert(std::make_shared<decl::Type>(
        nullptr, llvm::SMLoc { } ,"BOOLEAN",
        std::make_shared<type::Base>(type::Base::bt_BOOLEAN)
    ));
    scope.insert(std::make_shared<Type>(
        nullptr, llvm::SMLoc { }, "CHAR",
        std::make_shared<type::Base>(type::Base::bt_CHAR)
    ));
    scope.insert(std::make_shared<Type>(
        nullptr, llvm::SMLoc { }, "INTEGER",
        std::make_shared<type::Base>(type::Base::bt_INTEGER)
    ));
    scope.insert(std::make_shared<Type>(
        nullptr, llvm::SMLoc { }, "REAL",
        std::make_shared<type::Base>(type::Base::bt_REAL)
    ));
    scope.insert(std::make_shared<Type>(
        nullptr, llvm::SMLoc { }, "BYTE",
        std::make_shared<type::Base>(type::Base::bt_BYTE)
    ));
    scope.insert(std::make_shared<Type>(
        nullptr, llvm::SMLoc { }, "SET",
        std::make_shared<type::Base>(type::Base::bt_SET)
    ));
}
