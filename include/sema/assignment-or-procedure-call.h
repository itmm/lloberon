#pragma once

#include "context.h"

namespace sema {
	class Assignment_Or_Procedure_Call {
	public:
		explicit Assignment_Or_Procedure_Call(Context& context):
			context { context } { }

		Context& context;
	};
}