#include "engine/timer/CountdownTimer.h"

CountdownTimer::CountdownTimer(float seconds_to_finish, float starting_millisecs) 
    : Timer(starting_millisecs)
    , millisecs_to_finish_(seconds_to_finish / 1000.f)
    , did_finish_(false) {}

void CountdownTimer::Update(float dt) {
    Timer::Update(dt);
    did_finish_ = (elapsed_millisecs_ >= millisecs_to_finish_);
}

bool CountdownTimer::DidFinish() const {
    return did_finish_;
}

void CountdownTimer::Reset() {
    elapsed_millisecs_ = 0;
    did_finish_ = false;
}
