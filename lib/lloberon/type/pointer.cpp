#include "type/pointer.h"

std::shared_ptr<type::Pointer> type::Pointer::pointer_to_nil {
	std::make_shared<Pointer>(nullptr)
};