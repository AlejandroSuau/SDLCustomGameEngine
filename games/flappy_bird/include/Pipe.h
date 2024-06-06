#pragma once

#include <SDL2/SDL_image.h>

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/utils/Vec2.h"

enum class EVerticalAlignment {
    TOP,
    BOTTOM
};

class Pipe {
public:
    static const float kMinimumHeight;
    static const float kWidth;

    Pipe(Engine& engine, Vec2 position, float height);
    Pipe(Engine& engine, Vec2 position, Vec2 dimension);

    void Render();
    Rectangle GetRectangle() const;

    Vec2& GetPosition();

private:
    Engine& engine_;
    Vec2 position_;
    Vec2 dimension_;
    EVerticalAlignment vertical_alignment_;  
    SDL_Texture* texture_;

    void LoadTexture();
};
