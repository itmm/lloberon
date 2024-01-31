#include "type/pointer.h"

type::Pointer_Ptr type::Pointer::pointer_to_nil {
	std::make_shared<Pointer>(nullptr)
};