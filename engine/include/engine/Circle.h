#pragma once

#include "utils/Vec2.h"

class Circle {
public:
    Circle(float radius, Vec2 position);

    bool CollidesWith(const Circle& other);
    float DistanceWith(const Circle& other);

    float radius_;
    Vec2 center_;
};
