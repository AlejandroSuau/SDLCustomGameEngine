#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

class PipesPair {
public:
    PipesPair(Engine& engine, float x, float height_top, float height_bottom);

    void LoadTextures();

    bool DoesCollideWithPipe(const Rectangle& rect) const;
    bool DoesCollideWithScoreCheck(const Rectangle& rect) const;
    void RemoveCheckPoint();

    bool CanBeDestroyed() const;

    void Update(float dt);
    void Render();

private:
    Engine& engine_;
    Rectangle pipe_top_;
    Rectangle pipe_bottom_;
    SDL_Texture* pipe_texture_;
    std::unique_ptr<Rectangle> score_check_hit_box_;
};
