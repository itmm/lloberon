#pragma once

namespace lloberon {
    namespace token {
        enum Token_Kind : unsigned short {
            #define TOK(id) id,
            #include "lloberon/basic/token-kinds.def"
            NUM_TOKENS
        };

        const char* token_name(Token_Kind kind);
        const char* punctuator_spelling(Token_Kind kind);
        const char* keyword_spelling(Token_Kind kind);
    }
}