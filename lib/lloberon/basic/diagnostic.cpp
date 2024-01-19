#include "basic/diagnostic.h"

namespace {
	const char* diagnostic_texts[] = {
		#define DIAG(id, message) message,

		#include "basic/diagnostic.def"
	};
}

const char* Base_Diagnostic_Engine::diagnostic_text(
	unsigned int diagnostic_id
) {
	return diagnostic_texts[diagnostic_id];
}
