#include "snake/include/Food.h"

namespace {
    unsigned int kLayer = 4;
    unsigned int kMask = 1;
}

Food::Food(Engine& engine, Rectangle rect) 
    : engine_(engine)
    , rect_(rect)
    , is_marked_for_destroy_(false) {
    engine_.GetCollisionManager().AddCollidable(*this);
}

Food::~Food() {
    engine_.GetCollisionManager().RemoveCollidable(*this);
}

bool Food::IsMarkedForDestroy() const {
    return is_marked_for_destroy_;
}

void Food::Render() {
    engine_.DrawRectangle(rect_, {255, 153, 153, 255}, true);
}

const Rectangle& Food::GetBoundingBox() const {
    return rect_;
}

void Food::OnCollision(ICollidable& other) {
    is_marked_for_destroy_ = true;
}

unsigned int Food::GetLayer() const {
    return kLayer;
}

unsigned int Food::GetMask() const {
    return kMask;
}
