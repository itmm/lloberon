#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

class Ident_Def_Runner {
public:
    explicit Ident_Def_Runner(
        const char* source, lloberon::Ident_Def& ident_def, bool expected = false, bool has_more = false
    ):
        ident_def { ident_def }, source_mgr_ { }, diag_ { },
        lexer_ { initialize(source_mgr_, source), diag_ },
        expected_ { expected }, has_more_ { has_more },
        parser_ { lexer_ }
    { run(); }

    void run() {
        if (expected_) {
            EXPECT_TRUE(parser_.parse_ident_def(ident_def));
            EXPECT_GT(diag_.num_errors(), 0);
        } else {
            EXPECT_FALSE(parser_.parse_ident_def(ident_def));
            EXPECT_EQ(diag_.num_errors(), 0);
        }
        if (has_more_) {
            EXPECT_FALSE(parser_.is_eof());
        } else {
            EXPECT_TRUE(parser_.is_eof());
        }

    }

    lloberon::Ident_Def& ident_def;

private:
    static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
        source_mgr.AddNewSourceBuffer(
                llvm::MemoryBuffer::getMemBufferCopy(source),
                llvm::SMLoc()
        );
        return source_mgr;
    }
    llvm::SourceMgr source_mgr_;
    lloberon::Base_Diagnostic_Engine diag_;
    lloberon::Lexer lexer_;
    bool expected_;
    bool has_more_;
    lloberon::Parser parser_;
};

TEST(IDent_Def_Tests, empty) {
    lloberon::Ident_Def ident_def; ident_def.ident = "x"; ident_def.exported = true;
    Ident_Def_Runner { "", ident_def, true };
    EXPECT_STREQ(ident_def.ident.c_str(), "");
    EXPECT_FALSE(ident_def.exported);
}

TEST(Ident_Def_Tests, simple_ident) {
    lloberon::Ident_Def ident_def; ident_def.ident = "x"; ident_def.exported = true;
    Ident_Def_Runner { "abc", ident_def };
    EXPECT_STREQ(ident_def.ident.c_str(), "abc");
    EXPECT_FALSE(ident_def.exported);
}

TEST(Ident_Def_Tests, exported_ident) {
    lloberon::Ident_Def ident_def; ident_def.ident = "x"; ident_def.exported = false;
    Ident_Def_Runner { "abc*", ident_def };
    EXPECT_STREQ(ident_def.ident.c_str(), "abc");
    EXPECT_TRUE(ident_def.exported);
}

TEST(Ident_Def_Tests, empty_isnt_ident) {
    lloberon::Ident_Def ident_def; ident_def.ident = "x"; ident_def.exported = true;
    Ident_Def_Runner { "", ident_def, true };
    EXPECT_STREQ(ident_def.ident.c_str(), "");
    EXPECT_FALSE(ident_def.exported);
}

TEST(Ident_Def_Tests, number_isnt_ident) {
    lloberon::Ident_Def ident_def; ident_def.ident = "x"; ident_def.exported = true;
    Ident_Def_Runner { "123", ident_def, true, true };
    EXPECT_STREQ(ident_def.ident.c_str(), "");
    EXPECT_FALSE(ident_def.exported);
}

TEST(Ident_Def_Tests, star_isnt_ident) {
    lloberon::Ident_Def ident_def; ident_def.ident = "x"; ident_def.exported = true;
    Ident_Def_Runner("*", ident_def, true, true);
    EXPECT_STREQ(ident_def.ident.c_str(), "");
    EXPECT_FALSE(ident_def.exported);
}

#pragma clang diagnostic pop