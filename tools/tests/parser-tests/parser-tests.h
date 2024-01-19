#pragma once

#include "gtest/gtest.h"
#include "parser/parser.h"

template<bool (Parser::*METHOD)()>
class Parser_String_Runner {
public:
    explicit Parser_String_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        source_mgr_ { }, diag_ { },
        lexer_ { initialize(source_mgr_, source), diag_ },
        expected_ { expected }, has_more_ { has_more },
        parser_ { lexer_ }
    { run(); }

    void run() {
		bool failed;
		try {
			failed = (parser_.*METHOD)();
		}
		catch (const diag::Error&) { failed = true; }

        if (expected_) {
            EXPECT_TRUE(failed);
        } else {
            EXPECT_FALSE(failed);
        }
        if (has_more_) {
            EXPECT_FALSE(parser_.is_eof());
        } else {
            EXPECT_TRUE(parser_.is_eof());
        }

    }

private:
    static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
        source_mgr.AddNewSourceBuffer(
                llvm::MemoryBuffer::getMemBufferCopy(source),
                llvm::SMLoc()
        );
        return source_mgr;
    }
    llvm::SourceMgr source_mgr_;
    Base_Diagnostic_Engine diag_;
    Lexer lexer_;
    bool expected_;
    bool has_more_;
    Parser parser_;
};

template<typename VALUE, bool (Parser::*METHOD)(VALUE&)>
class Parser_Value_Runner {
public:
    explicit Parser_Value_Runner(
            const char* source, VALUE& value, bool expected = false, bool has_more = false
    ):
            source_mgr_ { }, diag_ { },
            lexer_ { initialize(source_mgr_, source), diag_ },
            expected_ { expected }, has_more_ { has_more },
            parser_ { lexer_ }, value_ { value }
    { run(); }

    void run() {
		bool failed;
		try {
			failed = (parser_.*METHOD)(value_);
		}
		catch (const diag::Error&) { failed = true; }
        if (expected_) {
            EXPECT_TRUE(failed);
        } else {
            EXPECT_FALSE(failed);
        }
        if (has_more_) {
            EXPECT_FALSE(parser_.is_eof());
        } else {
            EXPECT_TRUE(parser_.is_eof());
        }

    }

private:
    static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
        source_mgr.AddNewSourceBuffer(
                llvm::MemoryBuffer::getMemBufferCopy(source),
                llvm::SMLoc()
        );
        return source_mgr;
    }
    llvm::SourceMgr source_mgr_;
    Base_Diagnostic_Engine diag_;
    Lexer lexer_;
    bool expected_;
    bool has_more_;
    Parser parser_;
    VALUE& value_;
};

