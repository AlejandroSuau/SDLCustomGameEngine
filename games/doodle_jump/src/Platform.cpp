#include "doodle_jump/include/Platform.h"

namespace {
    static const float kWidth = 40.f;
    static const float kHeight = 10.f;

    static const unsigned int kLayer = 1;
    static const unsigned int kMask = 2;
}

Platform::Platform(Engine& engine, Vec2 position)
    : engine_(engine)
    , rect_(position.x, position.y, kWidth, kHeight) {
    engine_.GetCollisionManager().AddCollidable(*this);
}

Platform::~Platform() {
    engine_.GetCollisionManager().RemoveCollidable(*this);
}

void Platform::Update(float dt) {

}

Vec2 Platform::GetPosition() const {
    return {rect_.x, rect_.y};
}

void Platform::SetPosition(Vec2 position) {
    rect_.x = position.x;
    rect_.y = position.y;
}

void Platform::Render() {
    engine_.DrawRectangle(rect_, {255, 255, 255, 255});
}

const Rectangle& Platform::GetBoundingBox() const {
    return rect_;
}

void Platform::OnCollision(ICollidable& other) {

}

unsigned int Platform::GetLayer() const {
    return kLayer;
}

unsigned int Platform::GetMask() const {
    return kMask;
}