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

/* TODO
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