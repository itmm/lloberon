#pragma once

#include "type.h"

#include <memory>
#include <string>
#include <vector>

namespace type {
	class Record;

	using Record_Ptr = std::shared_ptr<Record>;

	class Record : public Type {
	public:
		Record(): Type { nullptr } { }

		Record_Ptr base;

		struct Entry {
			Entry(std::string name, Type_Ptr type, bool exported) :
				name { std::move(name) }, type { std::move(type) },
				exported { exported } { }

			const std::string name;
			Type_Ptr type;
			bool exported;
		};

		std::vector<Entry> entries;
	};
}