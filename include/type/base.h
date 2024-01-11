#pragma once

#include "type.h"

#include <memory>

namespace type {
	class Base : public Type {
	public:
		enum Kind {
			bt_BOOLEAN, bt_CHAR, bt_INTEGER, bt_REAL, bt_BYTE, bt_SET
		};

		explicit Base(Kind kind) : Type { }, kind_ { kind } { }

		bool is_bool() override { return kind_ == bt_BOOLEAN; }

		bool is_numeric() override {
			return kind_ == bt_INTEGER || kind_ == bt_REAL || kind_ == bt_BYTE;
		}

		bool is_integer() override {
			return kind_ == bt_INTEGER || kind_ == bt_BYTE;
		}

		[[nodiscard]] Kind base_kind() const { return kind_; }

		static std::shared_ptr<Base> base_boolean;
		static std::shared_ptr<Base> base_char;
		static std::shared_ptr<Base> base_integer;
		static std::shared_ptr<Base> base_real;
		static std::shared_ptr<Base> base_byte;
		static std::shared_ptr<Base> base_set;

	private:
		const Kind kind_;
	};
}