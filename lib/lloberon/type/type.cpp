#include "type/type.h"

type::Type_Ptr type::Type::base_boolean { std::make_shared<Type>() };

type::Type_Ptr type::Type::base_char { std::make_shared<Type>() };

type::Type_Ptr type::Type::base_integer { std::make_shared<Type>() };

type::Type_Ptr type::Type::base_real { std::make_shared<Type>() };

type::Type_Ptr type::Type::base_byte { std::make_shared<Type>() };

type::Type_Ptr type::Type::base_set { std::make_shared<Type>() };

bool type::Type::is_bool() {
	return this == &*type::Type::base_boolean;
}

bool type::Type::is_numeric() {
	return is_integer() || this == &*base_real;
}

bool type::Type::is_integer() {
	return this == &*base_integer || this == &*base_byte;
}