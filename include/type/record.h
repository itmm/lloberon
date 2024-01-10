#pragma once

#include "type.h"

#include <memory>
#include <string>
#include <vector>

namespace type {
	class Record : public Type {
	public:
		Record() = default;

		std::shared_ptr<Record> base;

		struct Entry {
			Entry(
				std::string name, std::shared_ptr<type::Type> type,
				bool exported
			) :
				name { std::move(name) }, type { std::move(type) },
				exported { exported } { }

			const std::string name;
			std::shared_ptr<type::Type> type;
			bool exported;
		};

		std::vector<Entry> entries;
	};
}