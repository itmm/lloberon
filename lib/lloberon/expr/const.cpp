#include "expr/const.h"

std::shared_ptr<expr::Const> expr::Const::true_value {
	std::make_shared<expr::Const>(true)
};

std::shared_ptr<expr::Const> expr::Const::false_value {
	std::make_shared<expr::Const>(false)
};