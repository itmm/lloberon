#pragma once

#include <string>
#include <vector>

namespace lloberon {
    class Ident_Def {
    public:
        Ident_Def(const std::string &ident = { }, bool exported = false):
            ident { ident }, exported { exported }
        { }

        std::string ident;
        bool exported;
    };

    using Ident_List = std::vector<Ident_Def>;
}