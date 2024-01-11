#include "type/base.h"

std::shared_ptr<type::Base> type::Base::base_boolean {
	std::make_shared<type::Base>(type::Base::bt_BOOLEAN)
};

std::shared_ptr<type::Base> type::Base::base_char {
	std::make_shared<type::Base>(type::Base::bt_CHAR)
};

std::shared_ptr<type::Base> type::Base::base_integer {
	std::make_shared<type::Base>(type::Base::bt_INTEGER)
};

std::shared_ptr<type::Base> type::Base::base_real {
	std::make_shared<type::Base>(type::Base::bt_REAL)
};

std::shared_ptr<type::Base> type::Base::base_byte {
	std::make_shared<type::Base>(type::Base::bt_BYTE)
};

std::shared_ptr<type::Base> type::Base::base_set {
	std::make_shared<type::Base>(type::Base::bt_SET)
};
