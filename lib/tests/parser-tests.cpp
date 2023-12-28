#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"
#include "gtest/gtest.h"
#include "lloberon/parser/parser.h"

class Parser_String_Runner {
public:
    explicit Parser_String_Runner(
        const char* source, bool (lloberon::Parser::* member)(),
        bool expected, bool has_more
    ):
        source_mgr_ { }, member_ { member }, diag_ { },
        lexer_ { initialize(source_mgr_, source), diag_ },
        expected_ { expected }, has_more_ { has_more },
        parser_ { lexer_ }
    { run(); }

    void run() {
        if (expected_) {
            EXPECT_TRUE((parser_.*member_)());
            EXPECT_GT(diag_.num_errors(), 0);
        } else {
            EXPECT_FALSE((parser_.*member_)());
            EXPECT_EQ(diag_.num_errors(), 0);
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
    bool (lloberon::Parser::* member_)();
    lloberon::Base_Diagnostic_Engine diag_;
    lloberon::Lexer lexer_;
    bool expected_;
    bool has_more_;
    lloberon::Parser parser_;
};

class Identdef_Runner: public Parser_String_Runner {
public:
    explicit Identdef_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_identdef, expected, has_more
        }
    { }
};

TEST(IdentDef_Tests, simple_ident) {
    Identdef_Runner("abc");
}

TEST(IdentDef_Tests, exported_ident) {
    Identdef_Runner("abc*");
}

TEST(IdentDef_Tests, empty_isnt_ident) {
    Identdef_Runner("", true);
}

TEST(IdentDef_Tests, number_isnt_ident) {
    Identdef_Runner("123", true, true);
}

TEST(IdentDef_Tests, star_isnt_ident) {
    Identdef_Runner("*", true, true);
}

class Identlist_Runner: public Parser_String_Runner {
public:
    explicit Identlist_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_identlist,
            expected, has_more
        }
    { }
};

TEST(Identlist_Tests, empty) {
    Identlist_Runner("", true);
}

TEST(Identlist_Tests, single) {
    Identlist_Runner("abc");
    Identlist_Runner("abc*");
}

TEST(Identlist_Tests, multiple) {
    Identlist_Runner("a, b*, c");
    Identlist_Runner("a*, b, c*");
    Identlist_Runner("a, b");
    Identlist_Runner("a*, b*");
}

TEST(Identlist_Tests, empty_items) {
    Identlist_Runner("a,", true);
    Identlist_Runner(",", true, true);
    Identlist_Runner("a,,b", true, true);
}

TEST(Identlist_Tests, wrong_items) {
    Identlist_Runner("1", true, true);
    Identlist_Runner("a,2", true, true);
}

class Qual_Ident_Runner: public Parser_String_Runner {
public:
    explicit Qual_Ident_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_qualident,
            expected, has_more
        }
    { }
};

TEST(Qual_Ident_Tests, empty) {
    Qual_Ident_Runner("", true);
}

TEST(Qual_Ident_Tests, simple) {
    Qual_Ident_Runner("a");
    Qual_Ident_Runner("a.b");
}

TEST(Qual_Ident_Tests, incomplete) {
    Qual_Ident_Runner("a.", true);
    Qual_Ident_Runner(".", true, true);
}

class Import_Runner: public Parser_String_Runner {
public:
    explicit Import_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_import,
            expected, has_more
        }
    { }
};

TEST(Import_Tests, empty) {
    Import_Runner("", true);
}

TEST(Import_Tests, simple) {
    Import_Runner("a");
    Import_Runner("a := b");
}

TEST(Import_Tests, missing) {
    Import_Runner("a b", false, true);
    Import_Runner("a :=", true);
}

class Import_List_Runner: public Parser_String_Runner {
public:
    explicit Import_List_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_import_list,
            expected, has_more
        }
    { }
};

TEST(Import_List_Tests, empty) {
    Import_List_Runner("", true);
}

TEST(Import_List_Tests, simple) {
    Import_List_Runner("IMPORT a;");
    Import_List_Runner("IMPORT a, b;");
    Import_List_Runner("IMPORT a := b, c;");
    Import_List_Runner("IMPORT a, b := c;");
    Import_List_Runner("IMPORT a := b, c := d;");
}

TEST(Import_List_Tests, missing) {
    Import_List_Runner("IMPORT", true);
    Import_List_Runner("IMPORT a", true);
    Import_List_Runner("IMPORT a,", true);
    Import_List_Runner("IMPORT a, b", true);
    Import_List_Runner("IMPORT a :=", true);
    Import_List_Runner("IMPORT a := b", true);
}

class Factor_Runner: public Parser_String_Runner {
public:
    explicit Factor_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_factor,
            expected, has_more
        }
    { }
};

TEST(Factor_Tests, empty) {
    Factor_Runner("", true);
}

TEST(Factor_Tests, literals) {
    Factor_Runner("3");
    Factor_Runner("3.241");
    Factor_Runner("\"abc\"");
    Factor_Runner("NIL");
    Factor_Runner("TRUE");
    Factor_Runner("FALSE");
}

TEST(Factor_Tests, set) {
    Factor_Runner("{3..5}");
}

TEST(Factor_Tests, grouped) {
    Factor_Runner("(3 + 4)");
}

TEST(Factor_Tests, ident) {
    Factor_Runner("a");
    Factor_Runner("a(3, TRUE)");
    Factor_Runner("a[3](TRUE)");
}

TEST(Factor_Tests, incomplete) {
    Factor_Runner("a(3,TRUE", true);
    Factor_Runner("a(3,", true);
    Factor_Runner("a(3", true);
    Factor_Runner("a(", true);
}

class Term_Runner: public Parser_String_Runner {
public:
    explicit Term_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_term,
            expected, has_more
        }
    { }
};

TEST(Term_Tests, empty) {
    Term_Runner("", true);
}

TEST(Term_Tests, single) {
    Term_Runner("3");
}

TEST(Term_Tests, simple) {
    Term_Runner("a * b");
    Term_Runner("a / b");
    Term_Runner("a DIV b");
    Term_Runner("a MOD b");
    Term_Runner("a & b");
}

TEST(Term_Tests, multiple) {
    Term_Runner("a * b * c");
    Term_Runner("a / 2 DIV b");
}

TEST(Term_Runner, incomplete) {
    Term_Runner("a / 2 DIV", true);
    Term_Runner("a /", true);
}

class Simple_Expression_Runner: public Parser_String_Runner {
public:
    explicit Simple_Expression_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_simple_expression,
            expected, has_more
        }
    { }
};

TEST(Test_Simple_Expressions, empty) {
    Simple_Expression_Runner("", true);
}

TEST(Test_Simple_Expression, single) {
    Simple_Expression_Runner("3");
}

TEST(Test_Simple_Expression, simple) {
    Simple_Expression_Runner("3 + 4");
    Simple_Expression_Runner("3 - 4");
    Simple_Expression_Runner("a OR b");
}

TEST(Test_Simple_Expression, factor) {
    Simple_Expression_Runner("3 * 4");
    Simple_Expression_Runner("3 / 2 + 4 * 3");
}

TEST(Test_Simple_Expression, unaries) {
    Simple_Expression_Runner("+3");
    Simple_Expression_Runner("-3 + 4");
    Simple_Expression_Runner("+-3", true, true);
}

TEST(Test_Simple_Expression, incomplete) {
    Simple_Expression_Runner("3 +", true);
    Simple_Expression_Runner("+", true);
}

class Expression_Runner: public Parser_String_Runner {
public:
    explicit Expression_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_expression,
            expected, has_more
        }
    { }
};

TEST(Expression_Tests, empty) {
    Expression_Runner("", true);
}

TEST(Expression_Tests, single) {
    Expression_Runner("3 = 4");
    Expression_Runner("3 # 4");
    Expression_Runner("3 < 4");
    Expression_Runner("3 <= 4");
    Expression_Runner("3 > 4");
    Expression_Runner("3 >= 4");
    Expression_Runner("3 IN a");
    Expression_Runner("a IS b");
}

TEST(Expression_Tests, multiple) {
    Expression_Runner("3 < 4 = TRUE");
}

TEST(Expression_Tests, invalid) {
    Expression_Runner("}", true);
}

class Const_Expression_Runner: public Parser_String_Runner {
public:
    explicit Const_Expression_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_const_expression,
            expected, has_more
        }
    { }
};

TEST(Const_Expression_Tests, empty) {
    Const_Expression_Runner("", true);
}

TEST(Const_Expression_Tests, literals) {
    Const_Expression_Runner("234");
    Const_Expression_Runner("-234");
    Const_Expression_Runner("2.34");
    Const_Expression_Runner("NIL");
    Const_Expression_Runner("TRUE");
    Const_Expression_Runner("FALSE");
}

TEST(Const_Expression_Tests, expressions) {
    Const_Expression_Runner("3 + 4 * 2");
    Const_Expression_Runner("2 < 4 # FALSE");
}

class Const_Declaration_Runner: public Parser_String_Runner {
public:
    explicit Const_Declaration_Runner(
        const char* source, bool expected = false, bool has_more = false
    ):
        Parser_String_Runner {
            source, &lloberon::Parser::parse_const_declaration,
            expected, has_more
        }
    { }
};

TEST(Const_Declaration_Tests, empty) {
    Const_Declaration_Runner("", true);
}

TEST(Const_Decalaration_Tests, simple) {
    Const_Declaration_Runner("a = 3 + 4");
}

TEST(Const_Declaration_Tests, incomplete) {
    Const_Declaration_Runner("a =", true);
    Const_Declaration_Runner("a", true);
}

class Element_Runner: public Parser_String_Runner {
public:
    explicit Element_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
            Parser_String_Runner {
                    source, &lloberon::Parser::parse_element,
                    expected, has_more
            }
    { }
};

TEST(Element_Tests, empty) {
    Element_Runner("", true);
}

TEST(Element_Tests, simple) {
    Element_Runner("3");
}

TEST(Element_Tests, range) {
    Element_Runner("3..6");
}

TEST(Element_Tests, incomplete) {
    Element_Runner("3..", true);
}

class Set_Runner: public Parser_String_Runner {
public:
    explicit Set_Runner(
            const char* source, bool expected = false, bool has_more = false
    ):
            Parser_String_Runner {
                    source, &lloberon::Parser::parse_set,
                    expected, has_more
            }
    { }
};

TEST(Set_Tests, empty) {
    Set_Runner("", true);
    Set_Runner("{}");
}

TEST(Set_Tests, simple) {
    Set_Runner("{1}");
    Set_Runner("{1, 2, 3}");
}

TEST(Set_Tests, ranges) {
    Set_Runner("{1..2}");
    Set_Runner("{1..2, 4..6}");
}

TEST(Set_Tests, incomplete) {
    Set_Runner("{1..3", true);
    Set_Runner("{1..}", true);
    Set_Runner("{1,}", true);
    Set_Runner("{1,,", true);
}

/*
        [[nodiscard]] bool parse();
        [[nodiscard]] bool parse_length();
        [[nodiscard]] bool parse_array_type();
        [[nodiscard]] bool parse_base_type();
        [[nodiscard]] bool parse_field_list();
        [[nodiscard]] bool parse_field_list_sequence();
        [[nodiscard]] bool parse_record_type();
        [[nodiscard]] bool parse_pointer_type();
        [[nodiscard]] bool parse_formal_type();
        [[nodiscard]] bool parse_formal_parameter_section();
        [[nodiscard]] bool parse_formal_parameters();
        [[nodiscard]] bool parse_procedure_type();
        [[nodiscard]] bool parse_type();
        [[nodiscard]] bool parse_type_declaration();
        [[nodiscard]] bool parse_variable_declaration();
        [[nodiscard]] bool parse_procedure_heading();
        [[nodiscard]] bool parse_procedure_body();
        [[nodiscard]] bool parse_procedure_declaration();
        [[nodiscard]] bool parse_declaration_sequence();
        [[nodiscard]] bool parse_module();
        [[nodiscard]] bool parse_expression_list();
        [[nodiscard]] bool parse_designator();
        [[nodiscard]] bool parse_actual_parameters();
        [[nodiscard]] bool parse_assignment_or_procedure_call();
        [[nodiscard]] bool parse_if_statement();
        [[nodiscard]] bool parse_label();
        [[nodiscard]] bool parse_label_range();
        [[nodiscard]] bool parse_case_list();
        [[nodiscard]] bool parse_case();
        [[nodiscard]] bool parse_case_statement();
        [[nodiscard]] bool parse_while_statement();
        [[nodiscard]] bool parse_repeat_statement();
        [[nodiscard]] bool parse_for_statement();
        [[nodiscard]] bool parse_statement();
        [[nodiscard]] bool parse_statement_sequence();
 */
#pragma clang diagnostic pop