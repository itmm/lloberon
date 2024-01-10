#pragma once

#include "const.h"

namespace expr {
    class Int_Literal: public Const {
    public:
        explicit Int_Literal(int value = 0): Const { }, value { value } { }
        int value;
    };
}