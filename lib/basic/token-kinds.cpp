#include "lloberon/basic/token-kinds.h"

using namespace lloberon;

static const char* const token_names[] = {
    #define TOK(id) #id,
    #define KEYWORD(id, flag) #id,
    #include "lloberon/basic/token-kinds.def"
    nullptr
};

const char* token::token_name(lloberon::token::Kind kind) {
    return token_names[kind];
}

const char* token::punctuator_spelling(lloberon::token::Kind kind) {
    switch (kind) {
        #define PUNCTUATOR(id, sp) case id: return sp;
        #include "lloberon/basic/token-kinds.def"
        default: break;
    }
    return nullptr;
}

const char* token::keyword_spelling(lloberon::token::Kind kind) {
    switch (kind) {
        #define KEYWORD(id, flag) case keyword_ ## id: return #id;
        #include "lloberon/basic/token-kinds.def"
        default: break;
    }
    return nullptr;
}