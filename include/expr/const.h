#pragma once

#include "expression.h"

#include <variant>

namespace expr {
	class Const : public Expression {
	public:
		explicit Const(bool value):
			Expression { type::Type::base_boolean }, values_ { value } { }

		explicit Const(int value):
			Expression { type::Type::base_integer }, values_ { value } { }

		explicit Const(double value):
			Expression { type::Type::base_real }, values_ { value } { }

		[[nodiscard]] bool is_bool() const {
			return std::holds_alternative<bool>(values_);
		}

		[[nodiscard]] bool is_int() const {
			return std::holds_alternative<int>(values_);
		}

		[[nodiscard]] bool is_real() const {
			return std::holds_alternative<double>(values_) || is_int();
		}

		[[nodiscard]] bool bool_value() const { return std::get<bool>(values_); }

		[[nodiscard]] int int_value() const { return std::get<int>(values_); }

		[[nodiscard]] double real_value() const {
			return is_int() ? int_value() : std::get<double>(values_);
		}

	private:
		std::variant<bool, int, double> values_;
	};
}