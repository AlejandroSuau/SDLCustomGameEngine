#include "engine/timer/Timer.h"

Timer::Timer(float starting_millisecs) 
    : starting_millisecs_(starting_millisecs)
    , elapsed_millisecs_(starting_millisecs) {}


void Timer::Update(float dt) {
    elapsed_millisecs_ += dt;
}

float Timer::GetElapsedMillisecs() const {
    return elapsed_millisecs_;
}
