#pragma once

#include <SDL2/SDL.h>

class Unit {
public:
    Unit(float x, float y);
    void Update(float dt);
    void Render(SDL_Renderer& renderer);

    void SetPosition(float x, float y);

    int GetX() const;
    int GetY() const;

private:
    float x_ {0.f};
    float y_ {0.f};
};
