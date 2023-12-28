#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "lloberon/parser/parser.h"
#include "lloberon/ast/ast.h"

using namespace lloberon;

bool Parser::parse() {
    return parse_module();
}

bool Parser::parse_simple_expression() {
    if (token_.is_one_of(token::plus, token::minus)) {
        advance();
    }
    if (parse_term()) { return true; }
    while (token_.is_one_of(token::plus, token::minus, token::keyword_OR)) {
        advance();
        if (parse_term()) { return true; }
    }
    return false;
}

bool Parser::parse_expression() {
    if (parse_simple_expression()) { return true; }
    while (token_.is_one_of(
        token::equals, token::not_equals, token::less, token::less_or_equal,
        token::greater, token::greater_or_equal, token::keyword_IS, token::keyword_IN
    )) {
        advance();
        if (parse_simple_expression()) { return true; }
    }
    return false;
}

bool Parser::parse_term() {
    if (parse_factor()) { return true; }
    while (token_.is_one_of(
        token::star, token::slash, token::keyword_DIV,
        token::keyword_MOD, token::andop
    )) {
        advance();
        if (parse_factor()) { return true; }
    }
    return false;
}

bool Parser::parse_element() {
    if (parse_expression()) { return true; }
    if (token_.is(token::range)) {
        advance();
        if (parse_expression()) { return true; }
    }
    return false;
}

bool Parser::parse_set() {
    if (consume(token::left_brace)) { return true; }
    if (! token_.is_one_of(token::right_brace, token::eof)) {
        if (parse_element()) { return true; }
        while (token_.is(token::comma)) {
            advance();
            if (parse_element()) { return true; }
        }
    }
    if (consume(token::right_brace)) { return true ; }
    return false;
}

bool Parser::parse_factor() {
    switch (token_.kind()) {
        case token::integer_literal: case token::float_literal: case token::string_literal:
        case token::keyword_NIL: case token::keyword_TRUE: case token::keyword_FALSE:
            advance();
            break;
        case token::left_brace:
            if (parse_set()) { return true; }
            break;

        case token::identifier:
            if (parse_designator()) { return true; }
            if (token_.is(token::left_parenthesis)) {
                if (parse_actual_parameters()) { return true; }
            }
            break;
        case token::left_parenthesis:
            advance();
            if (parse_expression()) { return true; }
            if (!consume(token::right_parenthesis)) { break; }
        LLVM_FALLTHROUGH; default:
            while (!token_.is_one_of(
                token::right_parenthesis, token::plus, token::minus,
                token::slash, token::star, token::eof
            )) {
                advance();
            }
            error();
            return true;
    }
    return false;
}

bool Parser::parse_import() {
    if (consume(token::identifier)) { return true; }
    if (token_.is(token::assign)) {
        advance();
        if (consume(token::identifier)) { return true; }
    }
    return false;
}

bool Parser::parse_import_list() {
    if (consume(token::keyword_IMPORT)) { return true; }
    if (parse_import()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_import()) { return true; }
    }
    if (consume(token::semicolon)) { return true; }
    return false;
}

bool Parser::parse_identdef() {
    if (consume(token::identifier)) { return true; }
    if (token_.is(token::star)) { advance(); }
    return false;
}

bool Parser::parse_const_expression() {
    return parse_expression();
}

bool Parser::parse_const_declaration() {
    if (parse_identdef()) { return true; }
    if (consume(token::equals)) { return true; }
    if (parse_const_expression()) { return true; }
    return false;
}

bool Parser::parse_qualident() {
    if (consume(token::identifier)) { return true; }
    if (token_.is(token::period)) {
        advance();
        if (consume(token::identifier)) { return true; }
    }
    return false;
}

bool Parser::parse_length() {
    return parse_const_expression();
}

bool Parser::parse_array_type() {
    if (consume(token::keyword_ARRAY)) { return true; }
    if (parse_length()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_length()) { return true; }
    }
    if (consume(token::keyword_OF)) { return true; }
    if (parse_type()) { return true; }
    return false;
}

bool Parser::parse_base_type() {
    if (parse_qualident()) { return true; }
    return false;
}

bool Parser::parse_identlist() {
    if (parse_identdef()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_identdef()) { return true; }
    }
    return false;
}

bool Parser::parse_field_list() {
    if (parse_identlist()) { return true; }
    if (consume(token::colon)) { return true; }
    if (parse_type()) { return true; }
    return false;
}

bool Parser::parse_field_list_sequence() {
    if (parse_field_list()) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_field_list()) { return true; }
    }
    return false;
}

bool Parser::parse_record_type() {
    if (consume(token::keyword_RECORD)) { return true; }
    if (token_.is(token::left_parenthesis)) {
        advance();
        if (parse_base_type()) { return true; }
        if (consume(token::right_parenthesis)) { return true; }
    }
    if (! token_.is(token::keyword_END)) {
        if (parse_field_list_sequence()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}

bool Parser::parse_pointer_type() {
    if (consume(token::keyword_POINTER)) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    if (parse_type()) { return true; }
    return false;
}

bool Parser::parse_formal_type() {
    while (token_.is(token::keyword_ARRAY)) {
        advance();
        if (consume(token::keyword_OF)) { return true; }
    }
    if (parse_qualident()) { return true; }
    return false;
}

bool Parser::parse_formal_parameter_section() {
    if (token_.is(token::keyword_VAR)) { advance(); }
    if (consume(token::identifier)) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (consume(token::identifier)) { return true; }
    }
    if (consume(token::colon)) { return true; }
    if (parse_formal_type()) { return true; }
    return false;
}

bool Parser::parse_formal_parameters() {
    if (consume(token::left_parenthesis)) { return true; }
    if (!token_.is(token::right_parenthesis)) {
        if (parse_formal_parameter_section()) { return true; }
        while (token_.is(token::semicolon)) {
            advance();
            if (parse_formal_parameter_section()) { return true; }
        }
    }
    if (consume(token::right_parenthesis)) { return true; }
    if (token_.is(token::colon)) {
        advance();
        if (parse_qualident()) { return true; }
    }
    return false;
}

bool Parser::parse_procedure_type() {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    if (parse_formal_parameters()) { return true; }
    return false;
}

bool Parser::parse_type() {
    if (token_.is(token::identifier)) {
        if (parse_qualident()) { return true; }
    } else if (token_.is(token::keyword_ARRAY)) {
        if (parse_array_type()) { return true; }
    } else if (token_.is(token::keyword_RECORD)) {
        if (parse_record_type()) { return true; }
    } else if (token_.is(token::keyword_POINTER)) {
        if (parse_pointer_type()) { return true; }
    } else if (token_.is(token::keyword_PROCEDURE)) {
        if (parse_procedure_type()) { return true; }
    } else { error(); return true; }
    return false;
}

bool Parser::parse_type_declaration() {
    if (parse_identdef()) { return true; }
    if (consume(token::equals)) { return true; }
    if (parse_type()) { return true; }
    return false;
}

bool Parser::parse_variable_declaration() {
    if (parse_identlist()) { return true; }
    if (consume(token::colon)) { return true; }
    if (parse_type()) { return true; }
    return false;
}

bool Parser::parse_procedure_heading() {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    if (parse_identdef()) { return true; }
    if (parse_formal_parameters()) { return true; }
    return false;
}

bool Parser::parse_procedure_body() {
    if (parse_declaration_sequence()) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        if (parse_statement_sequence()) { return true; }
    }
    if (token_.is(token::keyword_RETURN)) {
        advance();
        if (parse_expression()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}

bool Parser::parse_procedure_declaration() {
    if (parse_procedure_heading()) { return true; }
    if (consume(token::semicolon)) { return true; }
    if (parse_procedure_body()) { return true; }
    if (expect(token::identifier)) { return true; }
    advance();
    return false;
}

bool Parser::parse_declaration_sequence() {
    if (token_.is(token::keyword_CONST)) {
        advance();
        while (token_.is(token::identifier)) {
            if (parse_const_declaration()) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }
    if (token_.is(token::keyword_TYPE)) {
        advance();
        while (token_.is(token::identifier)) {
            if (parse_type_declaration()) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }
    if (token_.is(token::keyword_VAR)) {
        advance();
        while (token_.is(token::identifier)) {
            if (parse_variable_declaration()) { return true; }
            if (consume(token::semicolon)) { return true; }
        }
    }

    while (token_.is(token::keyword_PROCEDURE)) {
        if (parse_procedure_declaration()) { return true; }
        if (consume(token::semicolon)) { return true; }
    }
    return false;
}

bool Parser::parse_module() {
    if (consume(token::keyword_MODULE)) { return true; }
    if (expect(token::identifier)) { return true; }
    auto module_name { token_.identifier() };
    advance();
    if (consume(token::semicolon)) { return true; }
    if (token_.is(token::keyword_IMPORT)) {
        if (parse_import_list()) { return true; }
    }
    if (parse_declaration_sequence()) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        if (parse_statement_sequence()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    if (expect(token::identifier)) { return true; }
    if (module_name != token_.identifier()) { error(); return true; }
    advance();
    if (consume(token::period)) { return true; }
    if (expect(token::eof)) { return true; }
    return false;
}

bool Parser::parse_expression_list() {
    if (parse_expression()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_expression()) { return true; }
    }
    return false;
}

bool Parser::parse_designator() {
    if (parse_qualident()) { return true; }
    for (;;) {
        if (token_.is(token::period)) {
            advance();
            if (consume(token::identifier)) { return true; }
        } else if (token_.is(token::left_bracket)) {
            advance();
            if (parse_expression_list()) { return true; }
            if (consume(token::right_bracket)) { return true; }
        } else if (token_.is(token::ptr)) {
            advance();
//        } else if (token_.is(token::left_parenthesis)) {
//            advance();
//            parse_qualident();
//            if (consume(token::right_parenthesis)) { return; }
        } else { break; }
    }
    return false;
}

bool Parser::parse_actual_parameters() {
    if (consume(token::left_parenthesis)) { return true; }
    if (!token_.is(token::right_parenthesis)) {
        if (parse_expression_list()) { return true; }
    }
    if (consume(token::right_parenthesis)) { return true; }
    return false;
}

bool Parser::parse_assignment_or_procedure_call() {
    if (parse_designator()) { return true; }
    if (token_.is(token::assign)) {
        advance();
        if (parse_expression()) { return true; }
    } else {
        if (token_.is(token::left_parenthesis)) {
            if (parse_actual_parameters()) { return true; }
        }
    }
    return false;
}

bool Parser::parse_label() {
    if (token_.is_one_of(token::integer_literal, token::string_literal)) {
        advance();
    } else {
        if (parse_qualident()) { return true; }
    }
    return false;
}

bool Parser::parse_label_range() {
    if (parse_label()) { return true; }
    if (token_.is(token::range)) {
        advance();
        if (parse_label()) { return true; }
    }
    return false;
}

bool Parser::parse_case_list() {
    if (parse_label_range()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_label_range()) { return true; }
    }
    return false;
}

bool Parser::parse_case() {
    if (token_.is_one_of(token::bar, token::keyword_END)) { return true; }
    if (parse_case_list()) { return true; }
    if (consume(token::colon)) { return true; }
    if (parse_statement_sequence()) { return true; }
    return false;
}

bool Parser::parse_case_statement() {
    if (consume(token::keyword_CASE)) { return true; }
    if (parse_expression()) { return true; }
    if (consume(token::keyword_OF)) { return true; }
    if (parse_case()) { return true; }
    while (token_.is(token::bar)) {
        advance();
        if (parse_case()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}

bool Parser::parse_while_statement() {
    if (consume(token::keyword_WHILE)) { return true; }
    if (parse_expression()) { return true; }
    if (consume(token::keyword_DO)) { return true; }
    if (parse_statement_sequence()) { return true; }
    while (token_.is(token::keyword_ELSIF)) {
        advance();
        if (parse_expression()) { return true; }
        if (consume(token::keyword_DO)) { return true; }
        if (parse_statement_sequence()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}

bool Parser::parse_repeat_statement() {
    if (consume(token::keyword_REPEAT)) { return true; }
    if (parse_statement_sequence()) { return true; }
    if (consume(token::keyword_UNTIL)) { return true; }
    if (parse_expression()) { return true; }
    return false;
}

bool Parser::parse_for_statement() {
    if (consume(token::keyword_FOR)) { return true; }
    if (expect(token::identifier)) { return true; }
    advance();
    if (consume(token::assign)) { return true; }
    if (parse_expression()) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    if (parse_expression()) { return true; }
    if (token_.is(token::keyword_BY)) {
        advance();
        if (parse_const_expression()) { return true; }
    }
    if (consume(token::keyword_DO)) { return true; }
    if (parse_statement_sequence()) { return true; }
    if (consume(token::keyword_END)) { return true; }
    return false;
}

bool Parser::parse_statement() {
    if (token_.is(token::identifier)) {
        if (parse_assignment_or_procedure_call()) { return true; }
    } else if (token_.is(token::keyword_IF)) {
        if (parse_if_statement()) { return true; }
    } else if (token_.is(token::keyword_CASE)) {
        if (parse_case_statement()) { return true; }
    } else if (token_.is(token::keyword_WHILE)) {
        if (parse_while_statement()) { return true; }
    } else if (token_.is(token::keyword_REPEAT)) {
        if (parse_repeat_statement()) { return true; }
    } else if (token_.is(token::keyword_FOR)) {
        if (parse_for_statement()) { return true; }
    }
    return false;
}

bool Parser::parse_statement_sequence() {
    if (parse_statement()) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_statement()) { return true; }
    }
    return false;
}

bool Parser::parse_if_statement() {
    if (consume(token::keyword_IF)) { return true; }
    if (parse_expression()) { return true; }
    if(consume(token::keyword_THEN)) { return true; }
    if (parse_statement_sequence()) { return true; }
    while (token_.is(token::keyword_ELSIF)) {
        advance();
        if (parse_expression()) { return true; }
        if (consume(token::keyword_THEN)) { return true; }
        if (parse_statement_sequence()) { return true; }
    }
    if (token_.is(token::keyword_ELSE)) {
        advance();
        if (parse_statement_sequence()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}

#pragma clang diagnostic pop