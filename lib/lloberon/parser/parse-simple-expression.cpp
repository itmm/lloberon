#include "parser/parser.h"
#include "expr/integer.h"
#include "expr/bool.h"

bool Parser::parse_simple_expression(sema::Expression& simple_expression) {
    bool is_negative { false };
    if (token_.is_one_of(token::plus, token::minus)) {
        is_negative = token_.is(token::minus);
        advance();
    }
    Scope scope;
    if (parse_term(simple_expression)) { return true; }

    std::shared_ptr<expr::Integer> int_value;
    std::shared_ptr<expr::Bool> bool_value;

    int_value = std::dynamic_pointer_cast<expr::Integer>(simple_expression.expression);
    bool_value = std::dynamic_pointer_cast<expr::Bool>(simple_expression.expression);

    if (is_negative) {
        if (std::dynamic_pointer_cast<expr::Const>(simple_expression.expression)) {
            if (int_value) {
                int_value = std::make_shared<expr::Integer>(-int_value->value);
            } else { error(); return true; }
        }
    }

    while (token_.is_one_of(token::plus, token::minus, token::keyword_OR)) {
        auto op { token_.kind() };
        advance();
        if (parse_term(simple_expression)) { return true; }
        auto right_int_value { std::dynamic_pointer_cast<expr::Integer>(simple_expression.expression) };
        auto right_bool_value { std::dynamic_pointer_cast<expr::Bool>(simple_expression.expression) };
        if (int_value && right_int_value) {
            switch (op) {
                case token::plus:int_value = std::make_shared<expr::Integer>(int_value->value + right_int_value->value);
                    break;
                case token::minus:
                    int_value = std::make_shared<expr::Integer>(int_value->value - right_int_value->value);
                    break;
                default:
                    error();
                    return true;
            }
        } else if (bool_value && right_bool_value) {
            if (op == token::keyword_OR) {
                bool_value = std::make_shared<expr::Bool>(bool_value->value || right_bool_value->value);
            } else { error(); return true; }
        } else {
            int_value = nullptr;
            bool_value = nullptr;
        }
    }

    if (int_value) {
        simple_expression.expression = int_value;
    } else if (bool_value) {
        simple_expression.expression = bool_value;
    }
    return false;
}