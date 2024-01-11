#include "decl/type.h"
#include "sema/scope.h"
#include "type/type.h"

void decl::Type::register_base_types(Scope& scope) {
	static auto boolean_type { std::make_shared<decl::Type>(
		type::Type::base_boolean
	) };
	static auto char_type { std::make_shared<decl::Type>(
		type::Type::base_char
	) };
	static auto integer_type { std::make_shared<decl::Type>(
		type::Type::base_integer
	) };
	static auto real_type { std::make_shared<decl::Type>(
		type::Type::base_real
	) };
	static auto byte_type { std::make_shared<decl::Type>(
		type::Type::base_byte
	) };
	static auto set_type { std::make_shared<decl::Type>(
		type::Type::base_set
	) };

	scope.insert("BOOLEAN", boolean_type);
	scope.insert("CHAR", char_type);
	scope.insert("INTEGER", integer_type);
	scope.insert("REAL", real_type);
	scope.insert("BYTE", byte_type);
	scope.insert("SET", set_type);
}
