#pragma once

#include "scope.h"
#include "expr/const.h"

#include <vector>

namespace sema {
	struct Const_Case_Entry {
		Const_Case_Entry(
			const std::shared_ptr<expr::Const>& begin,
			const std::shared_ptr<expr::Const>& end
		): begin { begin }, end { end } { }

		std::shared_ptr<expr::Const> begin;
		std::shared_ptr<expr::Const> end;
	};

	using Const_Case_List = std::vector<Const_Case_Entry>;

	using Type_Case_List = std::vector<type::Type_Ptr>;
}