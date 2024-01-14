#pragma once

#include "expression.h"
#include "type/array.h"

#include <variant>
#include <string>

namespace expr {
	class Const : public Expression {
	public:
		explicit Const(bool value):
			Expression { type::Type::base_boolean }, values_ { value } { }

		explicit Const(int value):
			Expression { type::Type::base_integer }, values_ { value } { }

		explicit Const(double value):
			Expression { type::Type::base_real }, values_ { value } { }

		explicit Const(const std::string& value):
			Expression { std::make_shared<type::Array>(
				value.size(), type::Type::base_char
			) },
			values_ { value } { }

		explicit Const(unsigned value):
			Expression { type::Type::base_set }, values_ { value } { }

		[[nodiscard]] bool is_bool() const {
			return std::holds_alternative<bool>(values_);
		}

		[[nodiscard]] bool is_int() const {
			return std::holds_alternative<int>(values_);
		}

		[[nodiscard]] bool is_real() const {
			return std::holds_alternative<double>(values_) || is_int();
		}

		[[nodiscard]] bool is_string() const {
			return std::holds_alternative<std::string>(values_);
		}

		[[nodiscard]] bool is_set() const {
			return std::holds_alternative<unsigned>(values_);
		}

		[[nodiscard]] bool bool_value() const { return std::get<bool>(values_); }

		[[nodiscard]] int int_value() const { return std::get<int>(values_); }

		[[nodiscard]] double real_value() const {
			return is_int() ? int_value() : std::get<double>(values_);
		}

		[[nodiscard]] const std::string& string_value() const {
			return std::get<std::string>(values_);
		}

		[[nodiscard]] unsigned set_value() const {
			return std::get<unsigned>(values_);
		}

		static std::shared_ptr<Const> as_const(
			const std::shared_ptr<Expression>& expression
		) {
			return std::dynamic_pointer_cast<Const>(expression);
		}

		template<typename TYPE>
		static std::shared_ptr<Const> create(TYPE value) {
			return std::make_shared<Const>(value);
		}
	private:
		std::variant<bool, int, double, std::string, unsigned > values_;
	};
}