#pragma once

class Vec2 {
public:
    Vec2(float x, float y);
    
    float GetX() const;
    float GetY() const;

private:
    float x_;
    float y_;
};
