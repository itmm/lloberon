#pragma once

#include "context.h"
#include "stmt/statement.h"

namespace sema {
	class Statement_Sequence {
	public:
		Statement_Sequence() = default;

		stmt::Statement_Sequence sequence;
	};
}