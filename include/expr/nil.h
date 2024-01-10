#pragma once

#include "const.h"

namespace expr {
    class Nil: public Const {
    public:
        Nil() = default;
    };
}