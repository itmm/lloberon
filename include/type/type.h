#pragma once

#include <memory>
namespace type {
	class Type {
	public:
		virtual ~Type() = default;

		bool is_bool();

		bool is_numeric();

		bool is_integer();

		static std::shared_ptr<Type> base_boolean;

		static std::shared_ptr<Type> base_char;

		static std::shared_ptr<Type> base_integer;

		static std::shared_ptr<Type> base_real;

		static std::shared_ptr<Type> base_byte;

		static std::shared_ptr<Type> base_set;
	};
}