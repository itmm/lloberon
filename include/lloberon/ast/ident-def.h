#pragma once

#include <string>

namespace lloberon {
    class Ident_Def {
    public:
        Ident_Def() = default;
        std::string ident { };
        bool exported { false };
    };
}