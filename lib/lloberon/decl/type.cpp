#include "decl/type.h"
#include "sema/scope.h"
#include "type/base.h"

void decl::Type::register_base_types(Scope& scope) {
	scope.insert("BOOLEAN", std::make_shared<decl::Type>(
		std::make_shared<type::Base>(type::Base::bt_BOOLEAN)
	));
	scope.insert("CHAR", std::make_shared<Type>(
		std::make_shared<type::Base>(type::Base::bt_CHAR)
	));
	scope.insert("INTEGER", std::make_shared<Type>(
		std::make_shared<type::Base>(type::Base::bt_INTEGER)
	));
	scope.insert("REAL", std::make_shared<Type>(
		std::make_shared<type::Base>(type::Base::bt_REAL)
	));
	scope.insert("BYTE", std::make_shared<Type>(
		std::make_shared<type::Base>(type::Base::bt_BYTE)
	));
	scope.insert("SET", std::make_shared<Type>(
		std::make_shared<type::Base>(type::Base::bt_SET)
	));
}
