#pragma once

class Timer {
public:
    Timer(float starting_millisecs = 0.f);
    virtual ~Timer() = default;

    virtual void Update(float dt);
    float GetElapsedMillisecs() const;

protected:
    const float starting_millisecs_;
    float elapsed_millisecs_;
};
