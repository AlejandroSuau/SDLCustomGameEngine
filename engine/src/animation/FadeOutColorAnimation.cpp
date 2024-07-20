#pragma once

#include "engine/animation/FadeOutColorAnimation.h"

FadeOutColorAnimation::FadeOutColorAnimation(Color& color, float duration_in_seconds) 
    : color_(color)
    , timer_(duration_in_seconds, 0.f, false) {}

void FadeOutColorAnimation::Update(float dt) {
    timer_.Update(dt);
    if (timer_.DidFinish()) {
        color_.a = 0;
    } else {
        color_.a = static_cast<Uint8>(
            255 - (timer_.GetElapsedSeconds() * 255 / timer_.GetSecondsToFinish()));
    }
}

bool FadeOutColorAnimation::DidFinish() const {
    return timer_.DidFinish();
}
