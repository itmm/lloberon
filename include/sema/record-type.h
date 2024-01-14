#pragma once

#include <utility>

#include "scope.h"
#include "type/record.h"

namespace sema {
	class Record_Type {
	public:
		explicit Record_Type(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<type::Record> record {
			std::make_shared<type::Record>()
		};
	};
}