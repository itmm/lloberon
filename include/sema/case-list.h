#pragma once

#include "scope.h"
#include "expr/const.h"

#include <vector>

namespace sema {
	class Const_Case_List {
		public:
		explicit Const_Case_List(Context& context) : context { context } { }

		Context& context;

		struct Entry {
			Entry(
				const std::shared_ptr<expr::Const>& begin,
				const std::shared_ptr<expr::Const>& end
			): begin { begin }, end { end } { }

			std::shared_ptr<expr::Const> begin;
			std::shared_ptr<expr::Const> end;
		};
		std::vector<Entry> entries;
	};

	class Type_Case_List {
	public:
		explicit Type_Case_List(Context& context): context { context } { }

		Context& context;

		std::vector<std::shared_ptr<type::Type>> entries;
	};
}