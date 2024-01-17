#pragma once

#include "scope.h"

namespace sema {
	class Const_Label {
	public:
		explicit Const_Label() = default;

		std::shared_ptr<expr::Const> value;
	};

	class Const_Label_Range {
	public:
		explicit Const_Label_Range() = default;

		std::shared_ptr<expr::Const> begin;
		std::shared_ptr<expr::Const> end;
	};
}