#include "decl/type.h"
#include "sema/scope.h"
#include "type/base.h"

void decl::Type::register_base_types(Scope& scope) {
	scope.insert("BOOLEAN", std::make_shared<decl::Type>(
		type::Base::base_boolean
	));
	scope.insert("CHAR", std::make_shared<Type>(type::Base::base_char));
	scope.insert("INTEGER", std::make_shared<Type>(type::Base::base_integer));
	scope.insert("REAL", std::make_shared<Type>(type::Base::base_real));
	scope.insert("BYTE", std::make_shared<Type>(type::Base::base_byte));
	scope.insert("SET", std::make_shared<Type>(type::Base::base_set));
}
