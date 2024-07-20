#pragma once

#include "engine/timer/CountdownTimer.h"
#include "engine/Color.h"

class FadeOutColorAnimation {
public:
    FadeOutColorAnimation(Color& color, float duration_in_seconds);
    
    void Update(float dt);
    bool DidFinish() const;

private:
    Color& color_;
    CountdownTimer timer_;
};
