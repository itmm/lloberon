#pragma once

#include <memory>

#include "decl/declaration.h"

namespace type {
	class Type;

	using Type_Ptr = std::shared_ptr<Type>;

	class Type: public decl::Declaration {
	public:
		Type() = default;

		bool is_bool();

		bool is_numeric();

		bool is_integer();

		static Type_Ptr base_boolean;

		static Type_Ptr base_char;

		static Type_Ptr base_integer;

		static Type_Ptr base_real;

		static Type_Ptr base_byte;

		static Type_Ptr base_set;

	};
}