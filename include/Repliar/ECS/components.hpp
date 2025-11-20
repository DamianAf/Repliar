#pragma once

#include "Repliar/vector.hpp"

// TODO: implement the Sprite, Collider component

enum ComponentType {
    NONE = 0,
    TRANSFORM_COMPONENT = (1U << 0),
    SPRITE_COMPONENT = (1U << 1),
    COLLIDER_COMPONENT = (1U << 2),
    CUSTOM_COMPONENT = (1U << 3),
};

namespace Component {
struct Transform {
    Vector2<float> position;
    struct scale {
        float x{1.0f};
        float y{1.0f};
    };
    struct rotation {
        float x;
        float y;
        float z;
    };
};

struct Sprite {};

struct Collider {};
struct Custom {
    virtual ~Custom() = default;
};
} // namespace Component
