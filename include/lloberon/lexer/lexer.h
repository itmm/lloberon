#pragma once

#include "lloberon/basic/diagnostic.h"
#include "lloberon/lexer/token.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/SourceMgr.h"

namespace lloberon {
    class Keyword_Filter {
    public:
        void add_keywords();

        token::Token_Kind get_keyword(
            llvm::StringRef name, token::Token_Kind default_kind = token::unknown
        ) {
            auto result = hashtable_.find(name);
            if (result != hashtable_.end()) {
                return result->second;
            }
            return default_kind;
        }
    private:
        llvm::StringMap<token::Token_Kind> hashtable_;

        void add_keyword(llvm::StringRef keyword, token::Token_Kind kind);
    };

    class Lexer {
    public:
        explicit Lexer(llvm::SourceMgr& source_mgr, Diagnostics_Engine& diag):
            /* source_mgr_ { source_mgr }, */ diag_ { diag }
        {
            current_buffer_ = source_mgr.getMainFileID();
            current_str_ = source_mgr.getMemoryBuffer(current_buffer_)->getBuffer();
            current_ptr_ = current_str_.begin();
            keyword_filter_.add_keywords();
        }

        void next(Token &token);

        Diagnostics_Engine& diag() { return diag_; }
    private:
        // llvm::SourceMgr& source_mgr_;
        Diagnostics_Engine& diag_;
        unsigned current_buffer_;
        llvm::StringRef current_str_;
        const char* current_ptr_;
        Keyword_Filter keyword_filter_;

        void do_comment();
        void form_token(Token &result, const char *token_end, token::Token_Kind kind);
    };
}