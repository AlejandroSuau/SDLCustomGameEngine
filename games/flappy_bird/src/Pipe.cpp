#include "flappy_bird/include/Pipe.h"

#include "flappy_bird/include/Constants.h"

Pipe::Pipe(Engine& engine, Vec2 position, float height)
    : engine_(engine)
    , hit_box_(position.x, position.y, kPipeWidth, height)
    , vertical_alignment_((hit_box_.y == 0.f) ? EVerticalAlignment::TOP : EVerticalAlignment::BOTTOM) {
    LoadTexture();
}

void Pipe::LoadTexture() {
    texture_ = engine_.LoadTexture(kAssetsFolder + "pipe-green.png");
}

const Rectangle& Pipe::GetHitBox() const {
    return hit_box_;
}

void Pipe::SetPositionX(float x) {
    hit_box_.x = x;
}

float Pipe::GetPositionX() const {
    return hit_box_.x;
}

void Pipe::Render() {
    if (DEBUG) {
        engine_.DrawRectangle({hit_box_.x, hit_box_.y, hit_box_.w, hit_box_.h}, kPipeHitBoxColor);
    } else {
        engine_.RenderTexture(
            texture_,
            {hit_box_.x, hit_box_.y, hit_box_.w, hit_box_.h},
            (vertical_alignment_ == EVerticalAlignment::TOP) ? 180 : 0);
    }
}