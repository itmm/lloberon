#pragma once

#include "const.h"

namespace expr {
	class Const_Label {
	public:
		explicit Const_Label(const std::shared_ptr<Const>& value):
			value { value } { }

		std::shared_ptr<Const> value;
	};

	class Const_Label_Range {
	public:
		Const_Label_Range(const Const_Label& begin, const Const_Label& end):
 			begin { begin }, end { end } { }

		explicit Const_Label_Range(const Const_Label& value):
 			begin { value }, end { value } { }

		Const_Label begin;
		Const_Label end;
	};

	class Type_Label {
	public:
		explicit Type_Label(const std::shared_ptr<type::Type>& value):
			value { value } { }

		std::shared_ptr<type::Type> value;
	};
}