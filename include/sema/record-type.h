#pragma once

#include <utility>

#include "scope.h"
#include "type/record.h"

namespace sema {
	class Record_Type {
	public:
		Record_Type() = default;

		std::shared_ptr<type::Record> record {
			std::make_shared<type::Record>()
		};
	};
}