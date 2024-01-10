#include <vector>

#include "parser/parser.h"
#include "type/array.h"
#include "expr/int-literal.h"

bool Parser::parse_array_type(sema::Type& type) {
    type.clear();
    std::vector<int> counts;
    if (consume(token::keyword_ARRAY)) { return true; }
    sema::Const_Expression expression { type.scope() };
    if (parse_length(expression)) { return true; }
    counts.push_back(std::dynamic_pointer_cast<expr::Int_Literal>(expression.expression)->value);
    while (token_.is(token::comma)) {
        advance();
        if (parse_length(expression)) { return true; }
        counts.push_back(std::dynamic_pointer_cast<expr::Int_Literal>(expression.expression)->value);
    }
    if (consume(token::keyword_OF)) { return true; }
    sema::Type base { type.scope() };
    if (parse_type(base)) { return true; }
    std::shared_ptr<type::Type> current { base.type };
    for (auto i { counts.size() }; i; --i) {
        auto array { std::make_shared<type::Array>(counts[i - 1], current) };
        current = array;
    }
    type.type = current;
    return false;
}