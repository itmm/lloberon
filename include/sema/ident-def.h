#pragma once

#include <string>
#include <utility>
#include <vector>

namespace sema {
	class Ident_Def {
	public:
		explicit Ident_Def(std::string ident = { }, bool exported = false) :
			ident { std::move(ident) }, exported { exported } { }

		std::string ident;
		bool exported;

		void clear() {
			ident.clear();
			exported = false;
		}
	};

	using Ident_List = std::vector<Ident_Def>;
}