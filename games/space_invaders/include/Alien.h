#pragma once

#include <SDL2/SDL_image.h>

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/utils/Vec2.h"

#include <array>

enum class EAlienMovementDirection {
    RIGHT,
    LEFT,
    DOWN
};

class Alien {
public:
    Alien(Engine& engine, Vec2 position, std::array<Rectangle, 2> source_rects);

    void LoadTextures();
    void MovementStep(EAlienMovementDirection movement_direction);
    void Render();

    void SetStateMovingRight();
    void SetStateMovingLeft();

    void Hit();

    void SetPosition(Vec2 position);
    Vec2 GetPosition() const;
    bool IsAlive() const;

    const Rectangle& GetRectangle() const;

private:
    Engine& engine_;
    Rectangle rect_;
    SDL_Texture* texture_atlas_;
    std::array<Rectangle, 2> source_rects_;
    std::size_t current_source_index_;
    int lifes_;
};
