#pragma once

#include "context.h"
#include "stmt/statement.h"

namespace sema {
	class Statement_Sequence {
	public:
		explicit Statement_Sequence(Context& context) : context { context } { }

		Context& context;

		stmt::Statement_Sequence sequence;
	};
}