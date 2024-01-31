#include "basic/diagnostic.h"

namespace {
	const char* diagnostic_texts[] = {
		#define DIAG(id, message) message,

		#include "basic/diagnostic.def"
	};
}

namespace diag {
	const char* diagnostic_text(unsigned int diagnostic_id) {
		return diagnostic_texts[diagnostic_id];
	}

}