#include "engine/utils/Vec2.h"


Vec2::Vec2(float x, float y)
    : x_(x), y_(y) {}

float Vec2::GetX() const { return x_;  }

float Vec2::GetY() const { return y_; }
