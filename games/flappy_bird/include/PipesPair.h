#pragma once

#include "engine/Rectangle.h"

#include "Pipe.h"
#include "Bird.h"

class PipesPair {
public:
    static const float kPipesGap;

    PipesPair(Engine& engine, float x, float height_top, float height_bottom);

    bool DoesBirdCollidesWithAPipe(const Bird& bird) const;
    bool DoesBirdCollidesWithScoreCheck(const Bird& bird) const;
    void OnBirdCollisionWithScoreCheck();

    bool CanBeDestroyed() const;

    void Update(float dt);
    void Render();

private:
    Engine& engine_;
    Pipe pipe_top_;
    Pipe pipe_bottom_;
    std::unique_ptr<Rectangle> score_check_;
};
