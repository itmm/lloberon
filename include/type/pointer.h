#pragma once

#include "type.h"

#include <memory>

namespace type {
    class Pointer : public Type {
    public:
        explicit Pointer(std::shared_ptr<Type> points_to):
            points_to { std::move(points_to) }
        { }

        std::shared_ptr<Type> points_to; // TODO: use record type
    };
}