#pragma once

#include <SDL2/SDL_image.h>

#include "engine/Engine.h"
#include "engine/utils/Vec2.h"

#include <string>
#include <array>

class ScoreManager {
public:
    ScoreManager(Engine& engine);

    void Reset();
    void IncreaseScoreOneUnit();
    void Render();

private:
    Engine& engine_;
    int score_;
    std::string score_string_;
    Vec2 position_;

    std::array<SDL_Texture*, 10> number_textures_;

    void UpdateScoreValue(int val);
    void LoadNumberTextures();
};
