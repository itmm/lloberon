#include "gtest/gtest.h"
#include "lloberon/lexer/lexer.h"

static void expect_identifier(const lloberon::Token& token, const std::string& name) {
    EXPECT_EQ(token.kind(), lloberon::token::identifier);
    EXPECT_EQ(token.identifier().str(), name);
}

static void expect_eof(const lloberon::Token& token) {
    EXPECT_EQ(token.kind(), lloberon::token::eof);
}

static void expect_identifiers(const char* source, const char* first = nullptr, const char* second = nullptr) {
    llvm::SourceMgr source_mgr;
    lloberon::Diagnostics_Engine diag { source_mgr };
    source_mgr.AddNewSourceBuffer(llvm::MemoryBuffer::getMemBufferCopy(source), llvm::SMLoc());
    lloberon::Lexer lexer { source_mgr, diag };
    lloberon::Token token { };
    lexer.next(token);
    if (first) {
        expect_identifier(token, first);
        lexer.next(token);
    }
    if (second) {
        expect_identifier(token, second);
        lexer.next(token);
    }
    expect_eof(token);
}

void expect_empty(const char *source) {
    expect_identifiers(source);
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