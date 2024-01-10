#include "basic/token-kinds.h"

static const char* const token_names[] = {
	#define TOK(id) #id,
	#define KEYWORD(id, flag) #id,

	#include "basic/token-kinds.def"

	nullptr
};

const char* token::token_name(token::Kind kind) {
	return token_names[kind];
}

const char* token::punctuator_spelling(token::Kind kind) {
	switch (kind) {
		#define PUNCTUATOR(id, sp) case id: return sp;

		#include "basic/token-kinds.def"

		default:
			break;
	}
	return nullptr;
}

const char* token::keyword_spelling(token::Kind kind) {
	switch (kind) {
		#define KEYWORD(id, flag) case keyword_ ## id: return #id;

		#include "basic/token-kinds.def"

		default:
			break;
	}
	return nullptr;
}