#include "engine/timer/CountdownTimer.h"

CountdownTimer::CountdownTimer(float seconds_to_finish, float starting_seconds) 
    : Timer(starting_seconds)
    , seconds_to_finish_(seconds_to_finish)
    , did_finish_(false) {}

void CountdownTimer::Update(float dt) {
    Timer::Update(dt);
    did_finish_ = (elapsed_seconds_ >= seconds_to_finish_);
}

bool CountdownTimer::DidFinish() const {
    return did_finish_;
}

void CountdownTimer::Reset() {
    elapsed_seconds_ = 0;
    did_finish_ = false;
}

void CountdownTimer::AddSecondsToFinish(float seconds) {
    seconds_to_finish_ += seconds;
}

void CountdownTimer::SubtractSecondsToFinish(float seconds) {
    seconds_to_finish_ -= seconds;
    if (seconds_to_finish_ <= 0) {
        seconds_to_finish_ = .001f;
    }
}

float CountdownTimer::GetSecondsToFinish() const {
    return seconds_to_finish_;
}

void CountdownTimer::SetSecondsToFinish(float seconds_to_finish) {
    seconds_to_finish_ = seconds_to_finish;
}
