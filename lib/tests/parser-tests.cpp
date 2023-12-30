#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"
#include "gtest/gtest.h"
#include "lloberon/parser/parser.h"

template<bool (lloberon::Parser::*METHOD)()>
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
        if (expected_) {
            EXPECT_TRUE((parser_.*METHOD)());
            EXPECT_GT(diag_.num_errors(), 0);
        } else {
            EXPECT_FALSE((parser_.*METHOD)());
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
    lloberon::Base_Diagnostic_Engine diag_;
    lloberon::Lexer lexer_;
    bool expected_;
    bool has_more_;
    lloberon::Parser parser_;
};

using Identdef_Runner = Parser_String_Runner<&lloberon::Parser::parse_identdef>;

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

using Identlist_Runner = Parser_String_Runner<&lloberon::Parser::parse_identlist>;

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

using Factor_Runner = Parser_String_Runner<&lloberon::Parser::parse_factor>;

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

using Term_Runner = Parser_String_Runner<&lloberon::Parser::parse_term>;

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

using Simple_Expression_Runner = Parser_String_Runner<&lloberon::Parser::parse_simple_expression>;

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

using Expression_Runner = Parser_String_Runner<&lloberon::Parser::parse_expression>;

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

using Const_Expression_Runner = Parser_String_Runner<&lloberon::Parser::parse_const_expression>;

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

using Element_Runner = Parser_String_Runner<&lloberon::Parser::parse_element>;

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

using Set_Runner = Parser_String_Runner<&lloberon::Parser::parse_set>;

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

using Designator_Runner = Parser_String_Runner<&lloberon::Parser::parse_designator>;

TEST(Designator_Tests, empty) {
    Designator_Runner("", true);
}

TEST(Designator_Tests, simple) {
    Designator_Runner("a");
    Designator_Runner("a.b");
    Designator_Runner("a.b.c");
    Designator_Runner("a.b[2, 3]");
    Designator_Runner("a.b^");
}

TEST(Designator_Tests, combined) {
    Designator_Runner("a.b^[3].c^");
}

TEST(Designator_Tests, incomplete) {
    Designator_Runner("a[3,", true);
    Designator_Runner("a[3", true);
    Designator_Runner("a[3,]", true);
    Designator_Runner("a[]", true);
    Designator_Runner("a.b.", true);
    Designator_Runner("a.b.[", true, true);
    Designator_Runner("a.b.^", true, true);
    Designator_Runner("a.", true);
    Designator_Runner("a.[", true, true);
    Designator_Runner("a.^", true, true);
}

using Pointer_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_pointer_type>;

TEST(Pointer_Type_Tests, empty) {
    Pointer_Type_Runner("", true);
}

TEST(Pointer_Type_Tests, simple) {
    Pointer_Type_Runner("POINTER TO Record");
}

TEST(POINTER_Type_Tests, incomplete) {
    Pointer_Type_Runner("POINTER TO", true);
    Pointer_Type_Runner("POINTER Record", true, true);
}

using Import_Runner = Parser_String_Runner<&lloberon::Parser::parse_import>;

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

using Import_List_Runner = Parser_String_Runner<&lloberon::Parser::parse_import_list>;

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

using Qual_Ident_Runner = Parser_String_Runner<&lloberon::Parser::parse_qualident>;

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

using Const_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_const_declaration>;

TEST(Const_Declaration_Tests, empty) {
    Const_Declaration_Runner("", true);
}

TEST(Const_Decalaration_Tests, simple) {
    Const_Declaration_Runner("a* = 3 + 4");
}

TEST(Const_Declaration_Tests, incomplete) {
    Const_Declaration_Runner("a =", true);
    Const_Declaration_Runner("a", true);
}

using Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_type>;

TEST(Type_Tests, empty) {
    Type_Runner("", true);
}

TEST(Type_Tests, simple) {
    Type_Runner("INTEGER");
    Type_Runner("ARRAY 10 OF INTEGER");
    Type_Runner("RECORD x, y: INTEGER END");
    Type_Runner("POINTER TO Entry");
    Type_Runner("PROCEDURE (a: INTEGER): BYTE");
}

TEST(Type_Tests, invalid) {
    Type_Runner(":", true, true);
}

using Type_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_type_declaration>;

TEST(Type_Declaration_Tests, empty) {
    Type_Declaration_Runner("", true);
}

TEST(Type_Declaration_Tests, simple) {
    Type_Declaration_Runner("a* = INTEGER");
}

TEST(Type_Declaration_Tests, incomplete) {
    Type_Declaration_Runner("a =", true);
    Type_Declaration_Runner("a", true);
}

using Var_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_variable_declaration>;

TEST(Var_Declaration_Tests, empty) {
    Var_Declaration_Runner("", true);
}

TEST(Var_Declaration_Tests, simple) {
    Var_Declaration_Runner("a*: INTEGER");
}

TEST(Var_Declaration_Tests, incomplete) {
    Var_Declaration_Runner("a:", true);
    Var_Declaration_Runner("a", true);
}

TEST(Var_Declaration_Tests, invalid) {
    Var_Declaration_Runner("a INTEGER", true, true);
    Var_Declaration_Runner("a;", true, true);
}

using Declaration_Sequence_Runner = Parser_String_Runner<&lloberon::Parser::parse_declaration_sequence>;

TEST(Declaration_Sequence_Tests, empty) {
    Declaration_Sequence_Runner("");
}

TEST(Declaration_Sequence_Tests, single) {
    Declaration_Sequence_Runner("CONST a = 3;");
    Declaration_Sequence_Runner("TYPE image = ARRAY 10 OF INTEGER;");
    Declaration_Sequence_Runner("VAR a: INTEGER;");
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop;");
}

TEST(Declaration_Sequence_Tests, multiple) {
    Declaration_Sequence_Runner("CONST a = 3; b = 4;");
    Declaration_Sequence_Runner("TYPE X = INTEGER; Y = BYTE;");
    Declaration_Sequence_Runner("VAR a: INTEGER; b: BYTE;");
    Declaration_Sequence_Runner(
        "PROCEDURE Nop(); BEGIN END Nop; PROCEDURE Nop2(); BEGIN END Nop2;"
    );
}

TEST(Declaration_Sequence_Tests, multiple_types) {
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE;");
    Declaration_Sequence_Runner("TYPE x = BYTE; VAR a: BYTE;");
    Declaration_Sequence_Runner("VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; VAR a: BYTE;");
    Declaration_Sequence_Runner("TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; VAR a: BYTE;");
    Declaration_Sequence_Runner("TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
}

TEST(Declaration_Sequence_Tests, wrong_order) {
    Declaration_Sequence_Runner("TYPE x = BYTE; CONST a = 3;", false, true);
    Declaration_Sequence_Runner("VAR x: BYTE; CONST a = 3;", false, true);
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; CONST a = 3;", false, true);
    Declaration_Sequence_Runner("VAR x: BYTE; TYPE x: BYTE;", false, true);
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; TYPE x = BYTE;", false, true);
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; VAR x: BYTE;", false, true);
}

using If_Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_if_statement>;

TEST(If_Statement_Tests, empty) {
    If_Statement_Runner("", true);
}

TEST(If_Statement_Tests, simple) {
    If_Statement_Runner("IF cond THEN a := 1; b := TRUE END");
}

TEST(If_Statement_Tests, with_else) {
    If_Statement_Runner("IF cond THEN a := 1 ELSE a := 2; b := TRUE END");
}

TEST(If_Statement_Tests, with_elsif) {
    If_Statement_Runner("IF a < 3 THEN a := -1 ELSIF a > 3 THEN a := 1 ELSE a := 0 END");
}

using Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_statement>;

TEST(Statement_Tests, empty) {
    Statement_Runner("");
}

TEST(Statement_Tests, single) {
    Statement_Runner("a := 3");
    Statement_Runner("f(2, 3)");
    Statement_Runner("IF b THEN a := 3 END");
    Statement_Runner("CASE cond OF 3: a := 3 END");
    Statement_Runner("WHILE cond DO END");
    Statement_Runner("REPEAT UNTIL cond");
    Statement_Runner("FOR i := 1 TO 10 DO END");
}

TEST(Statement_Tests, invalid) {
    Statement_Runner("3", false, true);
}

using Statement_Sequence_Runner = Parser_String_Runner<&lloberon::Parser::parse_statement_sequence>;

TEST(Statement_Sequence_Tests, empty) {
    Statement_Sequence_Runner("");
}

TEST(Statement_Sequence_Runner, single) {
    Statement_Sequence_Runner("a := 3");
}

TEST(Statement_Sequence_Runner, multiple) {
    Statement_Sequence_Runner("a := 3;");
    Statement_Sequence_Runner("a := 3; b := 4");
    Statement_Sequence_Runner("a := 3; b := 4;");
}

using Module_Runner = Parser_String_Runner<&lloberon::Parser::parse_module>;

TEST(Module_Tests, empty) {
    Module_Runner("", true);
}

TEST(Module_Tests, simple) {
    Module_Runner("MODULE A; END A.");
}

TEST(Module_Tests, with_imports) {
    Module_Runner("MODULE A; IMPORT x := y; END A.");
}

TEST(Module_Tests, with_declarations) {
    Module_Runner("MODULE A; CONST B = 3; END A.");
}

TEST(Module_Tests, with_statements) {
    Module_Runner("MODULE A; BEGIN EXIT(10) END A.");
}

TEST(Module_Tests, with_multiple) {
    Module_Runner("MODULE A; IMPORT x; CONST B = 3; BEGIN EXIT(B) END A.");
    Module_Runner("MODULE A; IMPORT x; CONST B = 3; END A.");
    Module_Runner("MODULE A; IMPORT x; BEGIN EXIT(10) END A.");
    Module_Runner("MODULE A; CONST B = 3; BEGIN EXIT(B) END A.");
}

TEST(Module_Tests, names_dont_match) {
    Module_Runner("MODULE A; END B.", true, true);
}

TEST(MOdule_Tests, no_semicolon) {
    Module_Runner("MODULE A END A.", true, true);
}

TEST(Module_Tests, no_period) {
    Module_Runner("MODULE A; END A", true);
}

TEST(Module_Tests, no_names) {
    Module_Runner("MODULE END.", true, true);
    Module_Runner("MODULE A END.", true, true);
    Module_Runner("MODULE END A.", true, true);
}

TEST(Module_Tests, wrong_order) {
    Module_Runner("MODULE A; CONST B = 3; IMPORT x; END A.", true, true);
}

using Parse_Runner = Parser_String_Runner<&lloberon::Parser::parse>;

TEST(Parse_Tests, empty) {
    Parse_Runner("", true);
}

TEST(Parse_Tests, simple) {
    Parse_Runner("MODULE A; END A.");
}

TEST(Parse_Tests, invalid) {
    Parse_Runner("MODULE A END", true, true);
}

/* TODO
        [[nodiscard]] bool parse_length();
        [[nodiscard]] bool parse_array_type();
        [[nodiscard]] bool parse_base_type();
        [[nodiscard]] bool parse_field_list();
        [[nodiscard]] bool parse_field_list_sequence();
        [[nodiscard]] bool parse_record_type();
        [[nodiscard]] bool parse_formal_type();
        [[nodiscard]] bool parse_formal_parameter_section();
        [[nodiscard]] bool parse_formal_parameters();
        [[nodiscard]] bool parse_procedure_type();
        [[nodiscard]] bool parse_variable_declaration();
        [[nodiscard]] bool parse_procedure_heading();
        [[nodiscard]] bool parse_procedure_body();
        [[nodiscard]] bool parse_procedure_declaration();
        [[nodiscard]] bool parse_expression_list();
        [[nodiscard]] bool parse_actual_parameters();
        [[nodiscard]] bool parse_assignment_or_procedure_call();
        [[nodiscard]] bool parse_label();
        [[nodiscard]] bool parse_label_range();
        [[nodiscard]] bool parse_case_list();
        [[nodiscard]] bool parse_case();
        [[nodiscard]] bool parse_case_statement();
        [[nodiscard]] bool parse_while_statement();
        [[nodiscard]] bool parse_repeat_statement();
        [[nodiscard]] bool parse_for_statement();
 */
#pragma clang diagnostic pop