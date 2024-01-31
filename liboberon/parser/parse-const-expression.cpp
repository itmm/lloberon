#include "parser/parser.h"

expr::Const_Ptr Parser::parse_const_expression() {
	expr::Expression_Ptr expression { parse_expression() };
	auto const_value { std::dynamic_pointer_cast<expr::Const>(expression) };
	if (!const_value) {
		diag::report(diag::err_const_experssion_expected);
	}
	return const_value;
}