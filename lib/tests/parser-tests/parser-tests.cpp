#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

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

/*
    TODO: parse_procedure_type();
    TODO: parse_variable_declaration();
    TODO: parse_procedure_heading();
    TODO: parse_procedure_body();
    TODO: parse_procedure_declaration();
    TODO: parse_expression_list();
    TODO: parse_actual_parameters();
    TODO: parse_assignment_or_procedure_call();
    TODO: parse_label();
    TODO: parse_label_range();
    TODO: parse_case_list();
    TODO: parse_case();
    TODO: parse_case_statement();
    TODO: parse_while_statement();
    TODO: parse_repeat_statement();
    TODO: parse_for_statement();
 */

#pragma clang diagnostic pop