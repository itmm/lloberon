#include "gtest/gtest.h"
#include "lloberon/lexer/lexer.h"

class String_Runner {
public:
    explicit String_Runner(const char* source):
        source_mgr_ { }, diag_ { source_mgr_ },
        lexer { initialize(source_mgr_, source), diag_ }
    { lexer.next(token); }

    virtual ~String_Runner() = default;

    virtual void run() = 0;

private:
    static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
        source_mgr.AddNewSourceBuffer(
            llvm::MemoryBuffer::getMemBufferCopy(source),
            llvm::SMLoc()
        );
        return source_mgr;
    }
    llvm::SourceMgr source_mgr_;
    lloberon::Diagnostics_Engine diag_;
protected:
    lloberon::Lexer lexer;
    lloberon::Token token { };

    void expect_identifier(const std::string& name) {
        EXPECT_EQ(token.kind(), lloberon::token::identifier);
        EXPECT_EQ(token.identifier().str(), name);
    }
    void expect_eof() {
        EXPECT_EQ(token.kind(), lloberon::token::eof);
    }
};

class Single_Kind_Runner: public String_Runner {
    lloberon::token::Kind kind_;
public:
    Single_Kind_Runner(const char* source, lloberon::token::Kind kind):
        String_Runner(source), kind_ { kind }
    { }

    void run() override { EXPECT_EQ(token.kind(), kind_); }
};

class Identifiers_Runner: public String_Runner {
    const char* first_;
    const char* second_;
public:
    Identifiers_Runner(const char* source, const char* first, const char* second):
            String_Runner { source }, first_ { first }, second_ { second }
    { }

    void run() override {
        expect_identifier(first_);
        lexer.next(token);
        if (second_) {
            expect_identifier(second_);
            lexer.next(token);
        }
        expect_eof();
    }
};

static void expect_identifiers(const char* source, const char* first, const char* second = nullptr) {
    Identifiers_Runner(source, first, second).run();
}

void expect_empty(const char *source) {
    Single_Kind_Runner(source, lloberon::token::eof).run();
}

TEST(Empty_Tests, empty_file) {
    expect_empty("");
}

TEST(Empty_Tests, only_whitespace) {
    expect_empty(" ");
    expect_empty("  ");
}

TEST(Empty_Tests, only_comments) {
    expect_empty("(* *)");
    expect_empty(" (* a *) (* b *) ");
}

TEST(Identifier_Tests, one_char_identifier) {
    expect_identifiers("a", "a");
    expect_identifiers("  a  ", "a");
}

TEST(Identifier_Tests, identifier_can_contain_digits) {
    expect_identifiers("a2b3", "a2b3");
}

TEST(Identifier_Tests, tab_separates_identifiers) {
    expect_identifiers("a\tb", "a", "b");
}

TEST(Identifier_Tests, newline_separates_identifiers) {
    expect_identifiers("a\nb", "a", "b");
}

TEST(Identifier_Tests, comment_separates_identifiers) {
    expect_identifiers("a(* x y *)b", "a", "b");
}

TEST(Comments_Tests, minimal_comment) {
    expect_empty("(*)");
}

TEST(Comments_Tests, nested_comments) {
    expect_empty(" (* a (* b *) c *)");
}

TEST(Comments_Tests, multiple_comments) {
    expect_empty("(*)(*) (*) ");
}

TEST(Comments_Tests, star_line) {
    expect_empty("(***)");
}

static void expect_unknown(const char* source) {
    Single_Kind_Runner(source, lloberon::token::unknown).run();
}

TEST(Comments_Tests, open_comment) {
    expect_unknown("(*");
}
