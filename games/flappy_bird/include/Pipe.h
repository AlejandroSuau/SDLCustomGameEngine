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
    Pipe(Engine& engine, Vec2 position, float height);

    void Render();
    const Rectangle& GetHitBox() const;

    float GetPositionX() const;
    void SetPositionX(float x);

private:
    Engine& engine_;
    Rectangle hit_box_;
    EVerticalAlignment vertical_alignment_;  
    SDL_Texture* texture_;

    void LoadTexture();
};
