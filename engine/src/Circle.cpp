#include "engine/Circle.h"

#include <cmath>

Circle::Circle(float radius, Vec2 position) 
    : radius_(radius), center_(position.x + radius, position.y + radius) {}

bool Circle::CollidesWith(const Circle& other) {
    const auto d = DistanceWith(other);
    const auto radius_sum = radius_ + other.radius_;
    return (d < radius_sum);
}

float Circle::DistanceWith(const Circle& other) {
    const auto diff = other.center_ - center_;
    return sqrt(diff.x * diff.x + diff.y * diff.y);
}
