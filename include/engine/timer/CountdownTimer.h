#pragma once

#include "engine/timer/Timer.h"

class CountdownTimer : public Timer {
public:
    CountdownTimer(float seconds_to_finish, float starting_millisecs = 0.f);

    // Timer
    void Update(float dt) override;

    bool DidFinish() const;
    void Reset();

private:
    const float millisecs_to_finish_;
    bool did_finish_;
};
