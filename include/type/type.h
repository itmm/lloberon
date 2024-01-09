#pragma once

namespace type {
    class Type {
        public:
            virtual ~Type() = default;

            virtual bool is_bool() { return false; }
            virtual bool is_numeric() { return false; }
            virtual bool is_integer() { return false; }
    };
}