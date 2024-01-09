#pragma once

#include <utility>

#include "scope.h"
#include "type/type.h"

namespace sema {
    class Record_Type {
    public:
        explicit Record_Type(Scope& scope): scope_ { scope } { }

        Scope &scope() { return scope_; }

        void clear() { base_type = nullptr; entries.clear(); }

        std::shared_ptr<type::Type> base_type = nullptr;

        struct Entry {
            Entry(
                std::string  name, std::shared_ptr<type::Type> type,
                bool exported
            ):
                name {std::move( name )}, type { std::move(type) }, exported { exported }
            { }

            const std::string name;
            std::shared_ptr<type::Type> type;
            bool exported;
        };

        std::vector<Entry> entries;

    private:
        Scope& scope_;
    };
}