#pragma once

namespace lloberon::token {
    enum Kind : unsigned short {
        #define TOK(id) id,
        #include "lloberon/basic/token-kinds.def"
        // NUM_TOKENS
    };

    const char* token_name(Kind kind);
    const char* punctuator_spelling(Kind kind);
    const char* keyword_spelling(Kind kind);
}
