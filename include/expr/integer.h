#pragma once

#include "const.h"

namespace expr {
    class Integer: public Const {
    public:
        explicit Integer(int value = 0): Const { }, value { value } { }
        int value;
    };
}