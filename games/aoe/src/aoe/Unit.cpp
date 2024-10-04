#include "aoe/Unit.h"

#include <iostream>

static const int kWidth = 16;
static const int kHeight = 16;

Unit::Unit(float x, float y) : x_(x), y_(y) {
    std::cout << x_ << " " << y_ << "\n";
}

void Unit::Update(float dt) {

}

void Unit::Render(SDL_Renderer& renderer) {
    SDL_Rect r {static_cast<int>(x_), static_cast<int>(y_), kWidth, kHeight};
    SDL_RenderDrawRect(&renderer, &r);
}

void Unit::SetPosition(float x, float y) {
    x_ = x;
    y_ = y;
}

int Unit::GetX() const {
    return static_cast<int>(x_);
}

int Unit::GetY() const {
    return static_cast<int>(y_);
}