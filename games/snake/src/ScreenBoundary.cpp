#include "snake/include/ScreenBoundary.h"

namespace {
    unsigned int kLayer = 8;
    unsigned int kMask = 1;
}

ScreenBoundary::ScreenBoundary(Engine& engine, Snake& snake, Rectangle rect) 
    : engine_(engine)
    , snake_(snake)
    , rect_(rect) {
    engine_.GetCollisionManager().AddCollidable(*this);
}

ScreenBoundary::~ScreenBoundary() {
    engine_.GetCollisionManager().RemoveCollidable(*this);
}

void ScreenBoundary::Render() {
    engine_.DrawRectangle(rect_, {255, 255, 255, 255});
}

const Rectangle& ScreenBoundary::GetBoundingBox() const {
    return rect_;
}

void ScreenBoundary::OnCollision(ICollidable& other) {
    snake_.Die();
}

unsigned int ScreenBoundary::GetLayer() const {
    return kLayer;
}

unsigned int ScreenBoundary::GetMask() const {
    return kMask;
}
